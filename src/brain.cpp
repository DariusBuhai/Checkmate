//
// Created by Darius Buhai on 4/10/20.
//

#include "../include/brain.h"
#include "../include/rules.h"
#include "../include/piece.h"
#include "../include/types.h"
#include "../include/pieces.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

Brain::Brain(Rules* r)
{
    rules = r;
    initializeEvaluation();
}


void Brain::initializeEvaluation()
{
    vector<string> pt = {"pawn", "bishop", "knight", "queen", "rook", "king"};
    for(auto p: pt)
    {
        ifstream read("data/evaluation/"+p+".txt");
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
    //cout<<piece -> getType() << " " << pos.first  << " " << pos.second<< " are evaluarea " << evaluation[piece->getType()][pos.first][pos.second] << '\n';
    if(player==1)
        return evaluation[piece->getType()][pos.second][pos.first];
    return evaluation[piece->getType()][7-pos.second][7-pos.first];
}

Evaluation Brain :: evalAttacked(Piece* piece,  std::pair<int,int> position)
{
    Evaluation evalAttack;
    evalAttack.eval = 0;
    evalAttack.nr_pieces = 0;
    for(Piece* current : rules->getPieces())
    {
        if(current -> getPlayer() != piece -> getPlayer())
        {
            vector<pair<int, int>> futurePositions =rules->getFuturePositions(current,false);
            std::pair<int,int> pos = current -> getPos();
            /*cout<<current->getType()<<" " << pos.first + 1<< " " << 8 - pos.second<<'\n';
            for (auto x : futurePositions)
                cout<< x.first + 1 << " " << 8 - x.second <<'\n';
            */
            for(auto x : futurePositions)
                if(x.first == position.first && x.second == position.second)
                {
                    evalAttack.nr_pieces ++;
                    evalAttack.eval += getPointsEvaluation(current);
                }
        }
    }
    return evalAttack;
}

Evaluation Brain :: evalProtected(Piece* piece,  std::pair<int,int> position)
{
    Evaluation evalProtect;
    evalProtect.eval =  getPointsEvaluation(piece);
    evalProtect.nr_pieces = 1;
    int maxim = 0;
    for(Piece* current : rules->getPieces())
    {
        if(current -> getPlayer() == piece -> getPlayer())
        {
            vector<pair<int, int>> protectedPositions = rules->getProtectedPositions(current);
            std::pair<int,int> pos = current -> getPos();
            /*cout<<current->getType()<<" " << pos.first + 1<< " " << 8 - pos.second<<'\n';
            for (auto x : protectedPositions)
                cout<< x.first + 1 << " " << 8 - x.second <<'\n';
            */
            for(auto x : protectedPositions)
                if(x.first == position.first && x.second == position.second)
                {
                    cout<<current -> getType()<<'\n';
                    evalProtect.nr_pieces ++;
                    evalProtect.eval += getPointsEvaluation(current);
                    maxim = max ( maxim, evalProtect.eval);
                    break;
                }
        }

    }
    evalProtect.nr_pieces--;
    evalProtect.eval -= maxim;
    return evalProtect;
}

bool Brain :: isOkToMove(Piece* piece, std::pair<int,int> position)
{
    Evaluation evalProtect = evalProtected(piece,position);
    Evaluation evalAttack = evalAttacked(piece,position);
    int player = piece -> getPlayer();
    /*cout<<player<< " ";
    cout<<piece -> getType() << " " << position.first + 1 << " " << 8 - position.second<<'\n';
    cout<< evalAttack.nr_pieces << " " <<evalAttack.eval<<'\n';
    cout<< evalProtect.nr_pieces << " " <<evalProtect.eval<<'\n';
    */
    if(evalAttack.nr_pieces <= evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval)
        return 1;
    return 0;
}

bool Brain :: canCheck(Piece* piece, std::pair<int,int> position)
{
    std::pair<int,int> pos = piece -> getPos();
    Piece* aux_board[2][8][8];
    rules -> saveBoard(aux_board);
    /*board[1][position.first][position.second] = board[1][pos.first][pos.second];
    board[1][pos.first][pos.second] = nullptr;
    //board[1][position.first][position.second] -> changePos(position);
    //cout<< poz.first + 1 << " " << 8 - poz.second << '\n';
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8; j++)
        {
            if(board[1][j][i] != nullptr)
                cout<<board[1][j][i] -> getType()<<" ";
            else
                cout<<" nimic ";
        }
        cout<<'\n';
    }
    vector<pair<int, int>> futurePositions =rules->getFuturePositions(board[1][position.first][position.second],false);
    for (auto x : futurePositions)
        cout<< x.first + 1 << " " << 8 - x.second <<'\n';
    /*for(auto x : futurePositions)
        if(board[0][x.first][x.second] -> getType() == "king")
        {
            board[1][position.first][position.second] = nullptr;
            board[1][pos.first][pos.second] = piece;
            return true;
        }
    board[1][position.first][position.second] = nullptr;
    board[1][pos.first][pos.second] = piece;
    */
    return 0;
}
int Brain :: getmoves()
{
    return moves;
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

    for(Piece* piece: rules->getPieces())   ///ma plimb prin piese
        if(piece -> getPlayer() == 1)
        {
            for(auto pos: rules->getFuturePositions(piece))  ///ma plimb prin pozitiile in care poate ajunge fiecare piese
            {
                Piece* opPlayer = rules->getPiece(!piece->getPlayer(), pos); ///tipul pozitiei in care poate ajunge
                future_pos.emplace_back(Move(piece, pos));
                //cout << pos.first + 1 << " " << 8 - pos.second<<'\n';
                int eval = this->getEvaluation(piece, pos) * 10;
                std::pair<int,int> position = piece -> getPos();
                //cout<< piece -> getType() << " " <<position.first + 1<< " " <<  8 - position.second << " " << eval << '\n';
                ///evaluarea dupa sah
                ///sa nu muti piese in pozitiile unde ataca pisele adverse,facut
                ///sa nu muti cu aceeasi piesa de mai multe ori in primele 10 mutari
                ///sa muti piesele atacate
                ///sa isi apere piesele atacate
                if(canCheck(piece,pos) == 1 && isOkToMove(piece,pos) == 1)
                {
                    if(eval > best_eval_check)
                    {
                        best_eval_check = eval;
                        best_eval_check_move = Move(piece,pos);
                    }
                }
                else if(opPlayer == nullptr && eval > best_eval && isOkToMove(piece,pos) == 1)
                {
                    best_eval = eval;
                    best_eval_move = Move(piece, pos);
                }

                if(opPlayer != nullptr && opPlayer -> getType() != "king")
                {
                    if(piece -> getType() != "king")
                    {
                        int eval = getPointsEvaluation(opPlayer);
                        int evalpiece = getPointsEvaluation(piece);
                        if(evalpiece <= eval)
                        {
                            eval = eval - evalpiece;
                            if(eval>best_removed)
                            {
                                best_removed = eval;
                                best_removed_move = Move(piece, pos);
                            }
                        }
                        else
                        {
                            //cout<<opPlayer -> getType() << " " << piece -> getType()<<'\n';
                            Evaluation evalProtect = evalProtected(opPlayer,opPlayer -> getPos());
                            Evaluation evalAttack = evalAttacked(opPlayer,opPlayer -> getPos());
                            //cout<< evalAttack.nr_pieces << " " <<evalAttack.eval<<'\n';
                            //cout<< evalProtect.nr_pieces << " " <<evalProtect.eval<<'\n';
                            if(evalAttack.nr_pieces > evalProtect.nr_pieces || (evalAttack.nr_pieces > evalProtect.nr_pieces && evalAttack.eval <= evalProtect.eval) )
                            {
                                int eval = evalAttack.eval - evalProtect.eval;
                                if(eval>best_removed)
                                {
                                    best_removed = eval;
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
        }
    moves = moves + 2;
    if(future_pos.empty())
    {
        cout << "No moves found! Checkmate\n";
        return Move();
    }
    if(best_removed_move.piece != nullptr)
    {
        cout<<"Found the best piece to remove\n";
        return best_removed_move;
    }
    if(best_eval_check_move.piece != nullptr)
    {
        cout<<"Moving based on check\n";
        return best_eval_check_move;
    }
    if(best_eval_move.piece!= nullptr)
    {
        cout<<"Moving based on evaluation\n";
        return best_eval_move;
    }
    cout << "Moving to a random position\n";
    return future_pos[rand() % future_pos.size()];
}

