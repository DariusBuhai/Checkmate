#include <iostream>
#include <vector>
#include <utility>
#include <vector>

#include "../include/pieces.h"
#include "../include/piece.h"
#include "../include/types.h"

Pieces::Pieces(){
    this->initPositions();
}

void Pieces::initPositions()
{
    pieces.push_back(Rook({1, 7}, 0));
    pieces.push_back(Knight({2,7},0));
    pieces.push_back(Bishop({3,7},0));
    pieces.push_back(Queen({4,7},0));
    pieces.push_back(King({5,7},0));
    pieces.push_back(Bishop({6,7},0));
    pieces.push_back(Knight({7,7},0));
    pieces.push_back(Rook({8,7},0));
    for(int i = 1 ; i <= 8 ; i ++ )
        pieces.push_back(Pawn({i,6},0));
    pieces.push_back(Rook({1,0},1));
    pieces.push_back(Knight({2,0},1));
    pieces.push_back(Bishop({3,0},1));
    pieces.push_back(Queen({4,0},1));
    pieces.push_back(King({5,0},1));
    pieces.push_back(Bishop({6,0},1));
    pieces.push_back(Knight({7,0},1));
    pieces.push_back(Rook({8,0},1));
    for(int i = 1 ; i <= 8 ; i ++ )
        pieces.push_back(Pawn({i, 1},1));
}

void Pieces::displayPieces()
{
    for(auto x : pieces)
        std::cout<<"Piesa " << x.getType() << " " << x.getIsBlack() << " se afla pe pozitia " << x.getPos().first<< " " << x.getPos().second << '\n';
}

std::vector<Piece> Pieces::getPieces()
{
    //this->displayPieces();
    return pieces;
}
