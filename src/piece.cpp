#include <iostream>
#include <vector>
#include <utility>

#include "../include/piece.h"


// --------- piece methods ----------
Piece::Piece(int x_position, int y_position, bool color) : x_position(x_position), 
y_position(y_position), has_moved(false){}

void Piece::set_position(int x_next, int y_next)
{
    x_position = x_next;
    y_position = y_next;
}

bool Piece::isInTable(int x, int y)
{
    return ((x>= 1 && x<= 8) && (y>= 1 && y <= 8));
}

//---------- Pawn methods -----------

Pawn::Pawn(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
    name = "Pawn";
}


bool Pawn::isValidPosition(int x_next,int y_next)
{
    int dist = 1; //maximum distance it can move 
    if (!Piece::isInTable(x_next, y_next))
        return 0;
    if (has_moved == false)
        dist = 2;
    if (color == 0) //if it's white, it has to go up
        {
            if (x_next == x_position)
                if (y_next - y_position <= dist && y_next > y_position)
                    return 1;
        }
    if (color == 1) // it has to go down
        if (x_next == x_position)
            if (y_position - y_next <= dist && y_position > y_next)
                return 1;
    return 0;
}

std::vector<std::pair<int, int>> Pawn::path(int x_next, int y_next)
{
    std::vector< std::pair<int,int >> p;
    int posx, posy;
    posx = x_position;
    posy = y_position;
    // we go up
    if (y_next > y_position)
        while (posy < y_next)
        {
            posy ++ ;
            p.push_back(std::make_pair(posx, posy));
        }
    // we go down
    else
    {
        while (posy > y_next)
        {
            posy -- ;
            p.push_back(std::make_pair(posx, posy));
        }
    }
    p.clear();
    
}