#include "../include/brain.h"
#include <time.h>
#include "../include/Connector.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

ostream& operator<<(ostream& out, const Brain& ob)
{
    out<<"Au fost efectuate " << ob.moves << " mutari\n";
    out<<"Evaluarea pieselor este: \n";
    for(const auto& x : ob.evaluation)
    {
        out << x.first << '\n';
        for(const auto& v : x.second)
        {
            for(const auto& eval : v)
                out << eval << " ";
            out <<'\n';
        }
    }
    return out;
}

Brain::Brain(Rules* r)
{
    ConnectToEngine("stockfish.exe");
    rules = r;
    initializeEvaluation();
}
Brain::~Brain()
{
    CloseConnection();
}

void Brain::initializeEvaluation()
{
    vector<string> pt = {"pawn", "bishop", "knight", "queen", "rook", "king"};
    for(const auto& p: pt)
    {
        ifstream read("resources/evaluation/"+p+".txt");
        int x;
        evaluation[p].resize(8);
        for(int i=0; i<8; i++)
            for (int j = 0; j < 8; j++)
            {
                read>>x;
                evaluation[p][i].push_back(x);
            }
        read.close();
    }
}

int Brain::getPointsEvaluation(Piece* piece)
{
    if (dynamic_cast<Pawn *>(piece))
        return 10;
    if (dynamic_cast<Knight *>(piece))
        return 30;
    if (dynamic_cast<Bishop *>(piece))
        return 30;
    if (dynamic_cast<Rook *>(piece))
        return 50;
    if (dynamic_cast<Queen *>(piece))
        return 90;
    if (dynamic_cast<King *>(piece))
        return 900;
    return 0;
}

int Brain::getEvaluation(Piece* piece, pair<int,int> pos)
{
    if(player==1)
        return evaluation[piece->getType()][pos.second][pos.first];
    return evaluation[piece->getType()][7-pos.second][7-pos.first];
}

Evaluation Brain :: evalAttacked(Piece* piece,  std::pair<int,int> position)
{
    Evaluation evalAttack{};
    evalAttack.eval = 0;
    evalAttack.nr_pieces = 0;
    for(Piece* current : rules->getPieces())
    {
        if(current -> getPlayer() != piece -> getPlayer())
        {
            Evaluation evalProtect = evalProtected(piece,position);
            if((current -> getType() != "king") || (current -> getType() == "king" && evalProtect.nr_pieces == 0))
            {
                vector<pair<int, int>> futurePositions =rules->canAttackPos(current,current -> getPos());
                for(auto x : futurePositions)
                    if(x.first == position.first && x.second == position.second)
                    {
                        evalAttack.nr_pieces ++;
                        evalAttack.eval += getPointsEvaluation(current);
                    }
            }
        }
    }
    return evalAttack;
}

Evaluation Brain :: evalProtected(Piece* piece,  std::pair<int,int> position)
{
    Evaluation evalProtect{};
    evalProtect.eval =  getPointsEvaluation(piece);
    evalProtect.nr_pieces = 1;
    int maxim = getPointsEvaluation(piece);
    for(Piece* current : rules->getPieces())
        if(current -> getPlayer() == piece -> getPlayer() && current != piece)
        {

            vector<pair<int, int>> protectedPositions = rules->getProtectedPositions(current);

            /*if(current -> getType() == "rook" && position.first == 0 && position.second == 2)
            {
                for(auto x : protectedPositions)
                    cout<<x.first + 1 << " " << 8 - x.second << " ";
                cout<<'\n';
            }
            */
            for(auto x : protectedPositions)
                if(x.first == position.first && x.second == position.second)
                {
                    evalProtect.nr_pieces ++;
                    evalProtect.eval += getPointsEvaluation(current);
                    maxim = max ( maxim, getPointsEvaluation(current));
                    break;
                }
        }
    evalProtect.nr_pieces--;
    evalProtect.eval -= maxim;
    return evalProtect;
}

bool Brain :: isOkToMove(Piece* piece, std::pair<int,int> position)
{
    rules -> getCurentBoard(board);
    board[piece -> getPlayer()][position.first][position.second] = piece;
    board[piece -> getPlayer()][piece -> getPos().first][piece -> getPos().second] = nullptr;

    Evaluation evalProtect = evalProtected(piece,position);
    Evaluation evalAttack = evalAttacked(piece,position);
    //cout<<piece->getType() << " " << position.first + 1 << " "  << 8 - position.second << " " << evalProtect.eval << " " << evalAttack.eval << '\n';
    board[piece -> getPlayer()][position.first][position.second] = nullptr;
    board[piece -> getPlayer()][piece -> getPos().first][piece -> getPos().second] = piece;
    if(evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval)
        return true;
    return false;
    ///init statement
    /*
    if(auto evalProtect = evalProtected(piece,position), evalAttack = evalAttacked(piece,position);evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval)
        return true;
    return false;
    */
}

bool Brain :: canCheck(Piece* piece, std::pair<int,int> position)
{
    rules->getCurentBoard(board);
    /*
    for (int i = 0; i < 8; i++)
    {
        std::cout<<"\n";
        for (int j = 0; j < 8; j++)
            if (board[piece->getPlayer()][j][i] != nullptr)
                std::cout << board[piece->getPlayer()][j][i]->getType()<<" ";
            else
                std::cout << "nimic " ;
    }
    std::cout<<"\n\n";
    */
    if(board[0][position.first][position.second] != nullptr)
    {
        int eval = getPointsEvaluation(board[0][position.first][position.second]);
        int evalpiece = getPointsEvaluation(piece);
        if(eval < evalpiece)
            return false;
        else
        {
            Evaluation evalProtect = evalProtected(board[0][position.first][position.second],board[0][position.first][position.second] -> getPos());
            Evaluation evalAttack = evalAttacked(board[0][position.first][position.second],board[0][position.first][position.second] -> getPos());
            if(evalAttack.nr_pieces <= evalProtect.nr_pieces && (evalAttack.nr_pieces <= evalProtect.nr_pieces || evalAttack.eval > evalProtect.eval) )
                return false;
        }
    }
    std::pair<int,int> pos = piece -> getPos();
    //cout<< piece -> getType()<< " " << pos.first + 1 << " " << 8-  pos.second << " " << 1 + position.first << " " << 8 - position.second << '\n';
    board[1][position.first][position.second] = piece;
    board[1][pos.first][pos.second] = nullptr;
    vector<pair<int, int>> futurePositions =rules->getFuturePositions2(board[1][position.first][position.second],position,false);
    for(auto x : futurePositions)
        if(board[0][x.first][x.second] != nullptr && board[0][x.first][x.second] -> getType() == "king")
        {
            board[1][position.first][position.second] = nullptr;
            board[1][pos.first][pos.second] = piece;
            return true;
        }
    board[1][position.first][position.second] = nullptr;
    board[1][pos.first][pos.second] = piece;
    return false;
}

bool Brain :: Piece_Is_Attacked(Piece* piece, std::pair<int,int> position)
{
    Evaluation evalProtect = evalProtected(piece,position);
    Evaluation evalAttack = evalAttacked(piece,position);
    if(evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval)
        return false;
    return true;
}

int Brain :: getMoves()
{
    return moves;
}

inline void Brain::copyBoard()
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
            {
                boardBrain[i][j][k] = board[i][j][k];
            }
}

bool Brain :: check_last_3_moves(Move check_move)
{
    int n = last_AI_moves.size();
    if(n > 0 && last_AI_moves[n - 1].to == check_move.to && last_AI_moves[n - 1].from == check_move.from)
        return true;
    if(n > 1  && last_AI_moves[n - 2].to == check_move.to && last_AI_moves[n - 2].from == check_move.from)
        return true;
    if ( n > 2 && last_AI_moves[n - 3].to == check_move.to && last_AI_moves[n - 3].from == check_move.from)
        return true;
    return false;
}


Move Brain::determineBestMove()
{
    if(rules == nullptr)
        throw EXIT_FAILURE;

    vector<Move> future_pos;

    Move best_eval_move;
    int best_eval = -9999;
    Move best_removed_move;
    int best_removed = -9999;
    Move best_eval_check_move;
    int best_eval_check = -9999;
    Move best_attacked_move;
    int best_eval_attacked_piece = -9999;
    ///ma plimb prin piese

    rules->getCurentBoard(board);
    /*for (int i = 0; i < 8; i++)
    {
        std::cout<<"\n";
        for (int j = 0; j < 8; j++)
            if (board[1][j][i] != nullptr)
                std::cout << board[1][j][i]->getType()<<" ";
            else
                std::cout << "nimic " ;
    }
    std::cout<<"\n\n";
    */
    for(Piece* piece: rules->getPieces())
        if(piece -> getPlayer() == 1)
        {
            Move best_current_eval_move;
            int best_current_eval = -9999;
            ///ma plimb prin pozitiile in care poate ajunge fiecare piese
            for(auto pos: rules->getFuturePositions(piece))
            {
                Piece* opPlayer = rules->getPiece(!piece->getPlayer(), pos); ///tipul pozitiei in care poate ajunge
                future_pos.emplace_back(Move(piece, pos));
                //cout << pos.first + 1 << " " << 8 - pos.second<<'\n';
                int eval = this->getEvaluation(piece, pos) * 10;
                int evalpiece_AI = getPointsEvaluation(opPlayer);
                //cout<< piece -> getType() << " " <<position.first + 1<< " " <<  8 - position.second << " " << eval << '\n';
                ///evaluarea dupa sah
                ///sa nu muti piese in pozitiile unde ataca pisele adverse,facut
                ///sa nu muti cu aceeasi piesa de mai multe ori in primele 10 mutari
                ///sa muti piesele atacate,facut
                ///sa isi apere piesele atacate
                ///sa dea mat
                if(canCheck(piece,pos) == 1 && isOkToMove(piece,pos) == 1)
                {
                    if(eval > best_eval_check)
                    {
                        best_eval_check = eval;
                        best_eval_check_move = Move(piece,pos);
                    }
                }
                else
                {
                    if(opPlayer == nullptr && eval > best_current_eval && isOkToMove(piece,pos) == 1)
                    {
                        best_current_eval = eval;
                        best_current_eval_move = Move(piece,pos);
                    }
                    if(opPlayer == nullptr && eval > best_eval && isOkToMove(piece,pos) == 1)
                    {
                        best_eval = eval;
                        best_eval_move = Move(piece, pos);
                    }
                }

                if(opPlayer != nullptr && opPlayer -> getType() != "king")
                {
                    if(piece -> getType() != "king")
                    {
                        getPointsEvaluation(opPlayer);
                        int evalpiece_me = getPointsEvaluation(piece);
                        if(evalpiece_me <= evalpiece_AI)
                        {
                            if (evalpiece_AI > best_removed)
                            {
                                best_removed = evalpiece_AI;
                                best_removed_move = Move(piece, pos);
                            }
                        }
                        else
                        {
                            Evaluation evalProtect = evalProtected(opPlayer,opPlayer -> getPos());
                            Evaluation evalAttack = evalAttacked(opPlayer,opPlayer -> getPos());
                            if(evalAttack.nr_pieces > evalProtect.nr_pieces || (evalAttack.nr_pieces > evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval) )
                            {
                                //int eval = evalAttack.eval - evalProtect.eval;
                                if(evalpiece_AI > best_removed)
                                {
                                    best_removed = evalpiece_AI;
                                    best_removed_move = Move(piece, pos);
                                }
                            }
                        }
                    }
                    else
                    {
                        Evaluation evalProtect = evalProtected(opPlayer,opPlayer -> getPos());
                        if(evalProtect.nr_pieces == 0)
                        {
                            best_removed = 999;
                            best_removed_move = Move(piece,pos);
                        }
                    }
                }
            }
            ///verific daca piesa e atacata
            if(Piece_Is_Attacked(piece,piece->getPos()) == 1)
            {
                int evalPiece = getPointsEvaluation(piece);
                if(evalPiece > best_eval_attacked_piece)
                {
                    best_eval_attacked_piece = evalPiece;
                    best_attacked_move = best_current_eval_move;
                }
            }
        }
    moves += 2;
    if(future_pos.empty())
    {
        cout << "No moves found! Checkmate\n";
        return {};
    }
    if(best_removed_move.piece != nullptr)
    {
        cout<<"Found the best piece to remove\n";
        last_AI_moves.push_back(best_removed_move);
        return best_removed_move;
    }
    if(best_attacked_move.piece != nullptr)
    {
        cout<<"Found the best piece under attack to move u\n";
        last_AI_moves.push_back(best_attacked_move);
        return best_attacked_move;
    }
    if(best_eval_check_move.piece != nullptr && check_last_3_moves(best_eval_check_move) == false)
    {
        cout<<"Moving based on check\n";
        last_AI_moves.push_back(best_eval_check_move);
        return best_eval_check_move;
    }
    if(best_eval_move.piece!= nullptr && check_last_3_moves(best_eval_move) == false)
    {
        cout<<"Moving based on evaluation\n";
        last_AI_moves.push_back(best_eval_move);
        return best_eval_move;
    }
    cout << "Moving to a random position\n";
    return future_pos[rand() % future_pos.size()];
}

Move Brain::determine_Best_Stockfish_Move()
{
    rules->getCurentBoard(board);
    std::string best_move;
    Move Best_move;
    best_move = rules -> get_history();
    best_move = getNextMove(best_move);
    std::pair<int,int> pos_best_move;
    std::pair<int,int> pos_piece;
    pos_piece.first = int(best_move[0] - 97);
    pos_piece.second = 8 - (best_move[1] - '0');
    pos_best_move.first = int(best_move[2] - 97);
    pos_best_move.second = 8 - (best_move[3] - '0');
    cout<<best_move<<" cea mai buna mutare " << '\n';
    Piece* piece = board[1][pos_piece.first][pos_piece.second];
    Best_move = Move(piece,pos_best_move);
    //cout<<Best_move.piece -> getType() << " " << 1 + Best_move.from.first << " " << 8 - Best_move.from.second << " a mutat la " << 1 + Best_move.to.first << " " << 8 - Best_move.to.second<<'\n';
    return Best_move;
}
