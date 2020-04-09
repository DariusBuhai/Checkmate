#include <iostream>
#include <vector>
#include <utility>
#include <vector>

#include "../include/pieces.h"
//#include "../include/piece.h"
#include "../include/rules.h"
#include "../include/draw.h"
#include "../include/table.h"
#include "../include/types.h"

Pieces::Pieces(){
    this->initPieces();
    this->updateBoard();
}

Pieces::~Pieces(){
    for(auto &piece: pieces)
        (*piece).~Piece(),
        delete piece;
    pieces.clear();
}

void Pieces::initPieces(){
    pieces.push_back(new Rook({0, 7}, 0));
    pieces.push_back(new Knight({1,7},0));
    pieces.push_back(new Bishop({2,7},0));
    pieces.push_back(new Queen({3,7},0));
    pieces.push_back(new King({4,7},0));
    pieces.push_back(new Bishop({5,7},0));
    pieces.push_back(new Knight({6,7},0));
    pieces.push_back(new Rook({7,7},0));
    for(int i = 0 ; i < 8 ; i ++ )
        pieces.push_back(new Pawn({i,6},0));
    pieces.push_back(new Rook({0,0},1));
    pieces.push_back(new Knight({1,0},1));
    pieces.push_back(new Bishop({2,0},1));
    pieces.push_back(new Queen({3,0},1));
    pieces.push_back(new King({4,0},1));
    pieces.push_back(new Bishop({5,0},1));
    pieces.push_back(new Knight({6,0},1));
    pieces.push_back(new Rook({7,0},1));
    for(int i = 0 ; i < 8 ; i ++ )
        pieces.push_back(new Pawn({i, 1}, 1));
}

void Pieces::updateBoard() {
    for(int i=0;i<2;i++)
        for(int j=0;j<8;j++)
            for(int k=0;k<8;k++)
                board[i][j][k] = nullptr;
    for( unsigned int i=0;i<pieces.size();i++)
        board[(*(pieces[i])).getPlayer()][(*(pieces[i])).getPos().first][(*(pieces[i])).getPos().second] = pieces[i];
}

void Pieces::setPieces(std::vector<Piece*> new_pieces){
    for(auto piece: pieces)
        (*piece).~Piece();
    pieces.clear();
    for (auto it: new_pieces)
        pieces.push_back(it);
    this->updateBoard();
}


void Pieces::displayPieces(){
    for(auto x : pieces)
        std::cout<<"Piesa " << (*x).getType() << " " << (*x).getPlayer() << " se afla pe pozitia " << (*x).getPos().first<< " " << (*x).getPos().second << '\n';
}

std::vector<Piece*> Pieces::getPieces(){
    return pieces;
}

Piece* Pieces::getPiece(std::pair<int, int> position) {
    if(board[1][position.first][position.second]!= nullptr)
        return board[1][position.first][position.second];
    return board[0][position.first][position.second];
}

void Pieces::movePiece(Piece* piece, std::pair<int, int> new_position){
    history.emplace_back(Move(piece, piece->getPos(), new_position));

    std::cout<<history.back().from.first<<','<<history.back().from.second<<' ';
    std::cout<<history.back().to.first<<','<<history.back().to.second<<'\n';

    if(board[!piece->getPlayer()][new_position.first][new_position.second]!=nullptr){
        Piece* piece_to_delete = board[!piece->getPlayer()][new_position.first][new_position.second];
        int i = 0;
        for(;i<this->pieces.size();i++)
            if(pieces[i]==piece_to_delete)
                break;
        for(;i<this->pieces.size()-1;i++)
            pieces[i] = pieces[i+1];
        pieces.pop_back();
        delete piece_to_delete;
        board[!piece->getPlayer()][new_position.first][new_position.second] = nullptr;
    }

    piece->move(new_position);

    if(piece->getType()=="Pawn" && ((piece->getPlayer()==1 && piece->getPos().second==7) || (piece->getPlayer()==0 && piece->getPos().second==0))){
        for(int i=0;i<this->pieces.size();i++)
            if(pieces[i]==piece){
                pieces.push_back(new Queen(piece->getPos(), piece->getPlayer()));
                (*(pieces[i])).~Piece();
                delete (pieces[i]);
                pieces.erase(pieces.begin() + i);
            }
    }

    switchPlayer();
    updateBoard();
}

void Pieces::movePiece(std::pair<int, int> old_position, std::pair<int, int> new_position){
    Piece* piece = getPiece(old_position);
    if(piece!= nullptr)
        this->movePiece(piece, new_position);
}

int Pieces::getCurrentPlayer() {
    return current_player;
}

void Pieces::setCurrentPlayer(int player) {
    this->current_player = player;
}

void Pieces::switchPlayer() {
    this->current_player = !current_player;
}
