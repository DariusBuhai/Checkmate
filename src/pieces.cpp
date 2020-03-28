#include <iostream>
#include <vector>
#include <utility>

#include "../include/pieces.h"
#include "../include/types.h"

void Pieces::init_pieces_positions()
{
    pieces_positions.push_back({1,7,"Rook",0});
    pieces_positions.push_back({2,7,"Horse",0});
    pieces_positions.push_back({3,7,"Bishop",0});
    pieces_positions.push_back({4,7,"Queen",0});
    pieces_positions.push_back({5,7,"King",0});
    pieces_positions.push_back({6,7,"Bishop",0});
    pieces_positions.push_back({7,7,"Horse",0});
    pieces_positions.push_back({8,7,"Rook",0});
    for(int i = 1 ; i <= 8 ; i ++ )
    {
        pieces_positions.push_back({i,6,"Pawn",0});
    }
    pieces_positions.push_back({1,0,"Rook",1});
    pieces_positions.push_back({2,0,"Horse",1});
    pieces_positions.push_back({3,0,"Bishop",1});
    pieces_positions.push_back({4,0,"Queen",1});
    pieces_positions.push_back({5,0,"King",1});
    pieces_positions.push_back({6,0,"Bishop",1});
    pieces_positions.push_back({7,0,"Horse",1});
    pieces_positions.push_back({8,0,"Rook",1});
    for(int i = 1 ; i <= 8 ; i ++ )
    {
        pieces_positions.push_back({i, 1,"Pawn",1});
    }
}

void Pieces::get_pieces_positions()
{
    for(auto x : pieces_positions)
    {
        cout<<"Piesa " << x.type << " " << x.color << " se afla pe pozitia " << x.posx<< " " << x.posy << '\n';
    }
    //return pieces_positions;
}
