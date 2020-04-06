#include <iostream>
#include <vector>
#include <utility>
#include <vector>

#include "../include/pieces.h"
#include "../include/piece.h"
#include "../include/rules.h"

Pieces::Pieces(){
    this->initPieces();
    this->initBoard();
}

Pieces::~Pieces(){
    for(auto piece: pieces)
        piece.~Piece();
    pieces.clear();
}

void Pieces::initPieces(){
    pieces.push_back(Rook({0, 7}, 0));
    pieces.push_back(Knight({1,7},0));
    pieces.push_back(Bishop({2,7},0));
    pieces.push_back(Queen({3,7},0));
    pieces.push_back(King({4,7},0));
    pieces.push_back(Bishop({5,7},0));
    pieces.push_back(Knight({6,7},0));
    pieces.push_back(Rook({7,7},0));
    for(int i = 0 ; i < 8 ; i ++ )
        pieces.push_back(Pawn({i,6},0));
    pieces.push_back(Rook({0,0},1));
    pieces.push_back(Knight({1,0},1));
    pieces.push_back(Bishop({2,0},1));
    pieces.push_back(Queen({3,0},1));
    pieces.push_back(King({4,0},1));
    pieces.push_back(Bishop({5,0},1));
    pieces.push_back(Knight({6,0},1));
    pieces.push_back(Rook({7,0},1));
    for(int i = 0 ; i < 8 ; i ++ )
        pieces.push_back(Pawn({i, 1}, 1));
}

void Pieces::initBoard() {
    for(int i=0;i<2;i++)
        for(int j=0;j<8;j++)
            for(int k=0;k<8;k++)
                board[i][j][k] = nullptr;
    for(int i=0;i<pieces.size();i++)
        board[pieces[i].getIsBlack()][pieces[i].getPos().first][pieces[i].getPos().second] = &pieces[i];
}

void Pieces::setPieces(std::vector<Piece> new_pieces){
    pieces.clear();
    for (auto it: new_pieces)
        pieces.push_back(it);
}


void Pieces::displayPieces(){
    for(auto x : pieces)
        std::cout<<"Piesa " << x.getType() << " " << x.getIsBlack() << " se afla pe pozitia " << x.getPos().first<< " " << x.getPos().second << '\n';
}

std::vector<Piece> Pieces::getPieces(){
    return pieces;
}

Piece* Pieces::getPiece(std::pair<int, int> position) {
    if(board[1][position.first][position.second]!= nullptr)
        return board[1][position.first][position.second];
    return board[0][position.first][position.second];
}
