#include <iostream>
#include <vector>
#include <utility>

#include "../include/utils.h"
#include "../include/pieces.h"
#include "../include/piece.h"

#if defined(_WIN32)
    #include "piece.cpp"
#endif // defined

std::ostream& operator<<(std::ostream& out, const Pieces& ob)
{
    out<<"In momentul actual tabla arata asa: \n";
    for(int q = 0 ; q <= 1 ; q++){
        for (int i = 0; i < 8; i++){
            out<<"\n";
            for (int j = 0; j < 8; j++)
                if (ob.board[q][j][i] != nullptr)
                    out << ob.board[q][j][i]->getType()<<" ";
        }
        out<<"\n\n";
    }
    out<<"Mutarile efectuate sunt: \n";
    for(auto x : ob.history)
        out<<"Piesa " << x.piece -> getType() << " a mutat de la pozitia " << x.from.first << " " << x.from.second << " la pozitia " << x.to.first << " " << x.to.second << '\n';
    out<<"Piesele se afla la pozitiile: \n";
    for(auto x : ob.pieces){
        std::pair<int,int> pos = x -> getPos();
        out<<"Piesa " << x -> getType() << " se afla la pozitia " << pos.first << " " << pos.second << '\n';
    }
    return out;
}

Pieces::Pieces()
{

    resizeBoard();
    initPieces();
    updateBoard();
}

Pieces::~Pieces()
{
    /** Clear history and pieces */
    for(auto &piece: pieces)
        delete piece;
    for(auto &move: history)
    {
        delete move.updatedPiece;
        delete move.deletedPiece;
    }
    history.clear();
    pieces.clear();
}

std::string Pieces::get_history()
{
    std::string moves = "";
    for(auto x : history)
    {
        char c1 = char(x.from.first + 97);
        char c2 = 8 - x.from.second + '0';
        char c3 = char(x.to.first + 97);
        char c4 = 8 - x.to.second + '0';
        moves += c1;
        moves += c2;
        moves += c3;
        moves += c4;
        moves += " ";
        //std::cout<< c1 << c2 << c3 << c4 << '\n';
    }
    std::cout<<moves<<'\n';
    return moves;
}

void Pieces::resizeBoard()
{
    board.resize(2);
    for(int i=0; i<2; i++)
    {
        board[i].resize(8);
        for(int j=0; j<8; j++)
            board[i][j].resize(8);
    }
}

void Pieces::initPieces()
{
    PieceFactory newElement;

    pieces.push_back(newElement.createElement("Rook", {0, 7}, 0));
    pieces.push_back(newElement.createElement("Knight", {1, 7}, 0));
    pieces.push_back(newElement.createElement("Bishop", {2, 7}, 0));
    pieces.push_back(newElement.createElement("Queen", {3, 7}, 0));
    pieces.push_back(newElement.createElement("King", {4, 7}, 0));
    pieces.push_back(newElement.createElement("Bishop", {5, 7}, 0));
    pieces.push_back(newElement.createElement("Knight", {6, 7}, 0));
    pieces.push_back(newElement.createElement("Rook", {7, 7}, 0));

    // pieces.push_back(new Knight({1,7},0));
    // pieces.push_back(new Bishop({2,7},0));
    // pieces.push_back(new Queen({3,7},0));
    // pieces.push_back(new King({4,7},0));
    // pieces.push_back(new Bishop({5,7},0));
    // pieces.push_back(new Knight({6,7},0));
    // pieces.push_back(new Rook({7,7},0));

    for(int i = 0 ; i < 8 ; i ++ )
        pieces.push_back(newElement.createElement("Pawn", {i, 6}, 0));

    pieces.push_back(newElement.createElement("Rook", {0, 0}, 1));
    pieces.push_back(newElement.createElement("Knight", {1, 0}, 1));
    pieces.push_back(newElement.createElement("Bishop", {2, 0}, 1));
    pieces.push_back(newElement.createElement("Queen", {3, 0}, 1));
    pieces.push_back(newElement.createElement("King", {4, 0}, 1));
    pieces.push_back(newElement.createElement("Bishop", {5, 0}, 1));
    pieces.push_back(newElement.createElement("Knight", {6, 0}, 1));
    pieces.push_back(newElement.createElement("Rook", {7, 0}, 1));

    for(int i = 0 ; i < 8 ; i ++ )
        pieces.push_back(newElement.createElement("Pawn", {i, 1}, 1));


}

void Pieces::updateBoard()
{
    for(int i=0; i<2; i++)
        for(int j=0; j<8; j++)
            for(int k=0; k<8; k++)
                board[i][j][k] = nullptr;

    for(auto & piece : pieces)
        {
            //std::cout<<piece -> getType() << " " << piece ->getPos().first << " " << piece ->getPos().second << '\n';
            board[piece->getPlayer()][piece->getPos().first][piece->getPos().second] = piece;
        }
}

void Pieces::setPieces(const std::vector<Piece*>& new_pieces)
{
    for(auto piece: pieces)
        (*piece).~Piece();
    pieces.clear();
    for (auto it: new_pieces)
        pieces.push_back(it);
    updateBoard();
}


std::vector<Piece*> Pieces::getPieces()
{
    return pieces;
}

Piece* Pieces::getPiece(int player, std::pair<int, int> position)
{
    return board[player][position.first][position.second];
}


Piece* Pieces::operator[](std::pair<int, int> position)
{
    if(board[1][position.first][position.second] != nullptr)
        return board[1][position.first][position.second];
    return board[0][position.first][position.second];
}

std::vector<std::vector<Piece*>> Pieces::operator[](int player)
{
    return this->board[player];
}

void Pieces::movePiece(Piece* piece, std::pair<int, int> new_position, bool has_taken_piece)
{
    Move current_move = Move(piece, piece->getPos(), new_position);

    std::cout<<current_move.from.first<<','<<current_move.from.second<<' ';
    std::cout<<current_move.to.first<<','<<current_move.to.second<<'\n';

    int player = piece->getPlayer();
    //if we go up or down
    int dst = 1;
    if (player == 1)
        dst = -1;
    ///castle
    if(board[piece->getPlayer()][new_position.first][new_position.second] != nullptr)
    {
        Piece* aux = board[piece->getPlayer()][new_position.first][new_position.second];
        if(new_position.first > piece->getPos().first)
        {
            aux->move(piece->getPosCastleShort());
            new_position.first -=1;
        }
        else
        {
            aux->move(piece->getPosCastleLong());
            new_position.first +=2;
        }
        piece->move(new_position);
        switchPlayer();
        updateBoard();
        return;
    }
    ///take piece
    if(board[!piece->getPlayer()][new_position.first][new_position.second]!=nullptr)
    {
        Piece* piece_to_delete = board[!piece->getPlayer()][new_position.first][new_position.second];
        /// Remember the address of the piece, but don't delete it
        current_move.deletedPiece = piece_to_delete;
        unsigned int i = 0;
        for(; i<pieces.size(); i++)
            if(pieces[i]==piece_to_delete)
                break;

        pieces.erase(pieces.begin() + i);
        board[!piece->getPlayer()][new_position.first][new_position.second] = nullptr;
    }
    ///en passant
    else if(board[!piece->getPlayer()][new_position.first][new_position.second] == nullptr && piece->getType() == "pawn" && ((piece->getPos().first == new_position.first + 1) || (piece->getPos().first == new_position.first - 1)) )
    {
        Piece* piece_to_delete = board[!piece->getPlayer()][new_position.first][new_position.second + dst];
        current_move.deletedPiece = piece_to_delete;

        unsigned int i = 0;
        for(; i<pieces.size(); i++)
            if(pieces[i]==piece_to_delete)
                break;
        pieces.erase(pieces.begin() + i);
        board[!piece->getPlayer()][new_position.first][new_position.second + dst] = nullptr;
    }
    piece->move(new_position);
    if(dynamic_cast<Pawn*>(piece) && ((piece->getPlayer()==1 && piece->getPos().second==7) || (piece->getPlayer()==0 && piece->getPos().second==0)))
    {
        for(unsigned int i=0; i<pieces.size(); i++)
            if(pieces[i]==piece)
            {
                current_move.updatedPiece = piece;
                Piece * newPiece = new Queen(piece->getPos(), piece->getPlayer());
                current_move.piece = newPiece;
                pieces.push_back(newPiece);
                pieces.erase(pieces.begin() + i);
                break;
            }
    }

    history.emplace_back(current_move);

    switchPlayer();
    updateBoard();
}

void Pieces::movePiece(std::pair<int, int> old_position, std::pair<int, int> new_position)
{
    Piece* piece = operator[](old_position);
    if(piece!= nullptr)
        movePiece(piece, new_position);
}

int Pieces::getCurrentPlayer()
{
    return currentPlayer;
}

void Pieces::setCurrentPlayer(int player)
{
    currentPlayer = player;
}

void Pieces::switchPlayer()
{
    currentPlayer = !currentPlayer;
}


void Pieces::resetGame()
{
    /** Clear history and pieces */
    for(auto &piece: pieces)
        delete piece;
    for(auto &move: history)
    {
        delete move.updatedPiece;
        delete move.deletedPiece;
    }
    history.clear();
    pieces.clear();

    initPieces();
    updateBoard();
    currentPlayer = 0;
}

void Pieces::undoMove()
{
    if(!history.empty())
    {
        Move current_move = history.back();

        if(current_move.updatedPiece!=nullptr)
        {

            for(auto &piece: pieces)
                if(piece==current_move.piece)
                {
                    piece = current_move.updatedPiece;
                    break;
                }
            delete current_move.piece;
            current_move.piece = current_move.updatedPiece;
        }

        current_move.piece->move(current_move.from);
        switchPlayer();
        if(dynamic_cast<Pawn*>(current_move.piece) && ((current_move.piece->getPlayer()==0 && current_move.piece->getPos().second==6) || (current_move.piece->getPlayer()==1 && current_move.piece->getPos().second==1)))
            current_move.piece->resetHasMoved();

        if(current_move.deletedPiece!= nullptr)
            this->pieces.push_back(current_move.deletedPiece);

        updateBoard();
        history.pop_back();
    }
}
