#include <iostream>
#include <vector>
#include <utility>

#include "../include/piece.h"


// ------------- piece methods ---------------
Piece::Piece(int x_position, int y_position, bool color) : x_position(x_position), 
y_position(y_position), has_moved(false), color(color){}

void Piece::set_position(int x_next, int y_next)
{
    x_position = x_next;
    y_position = y_next;
}
bool Piece::isInTable(int x, int y)
{
    return ((x>= 1 && x<= 8) && (y>= 1 && y <= 8));
}

//--------------- Pawn methods ---------------

Pawn::Pawn(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
    name = "Pawn";
}

void Pawn::move(int x_next, int y_next)
{
	has_moved = true;
	x_position = x_next;
	y_position = y_next;
}


std::vector<std::vector<std::pair<int, int>>> Pawn::path()
{
    std::vector<std::vector< std::pair<int,int >>> p;
	p.resize(1);
    int posx, posy;
    posx = x_position;
    posy = y_position;
	int dist = 1;
	if (has_moved == 1)
		dist = 2;
    // we go down, we are white
    if (color == 1)
        while (posy < y_position + dist)
        {
            posy ++ ;
            p[0].push_back(std::make_pair(posx, posy));
        }
    // we go up, we are black
    else
    {
        while (posy > y_position - dist)
        {
            posy -- ;
            p[0].push_back(std::make_pair(posx, posy));
        }
    }
	return p;
}

//-------------- Rook Methods --------

Rook::Rook(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
	name = "Rook";
}

std::vector<std::vector<std::pair<int, int>>> Rook::path()
{
	std::vector<std::vector< std::pair<int, int >>> p;
	p.resize(4);
	//it can go up, down, left, right;
	//---- first we go up
	int posx, posy;
	posx = x_position, posy = y_position;
	//left
	while (posx > 0)
		posx--, p[0].push_back(std::make_pair(posx, posy));
	posx = x_position, posy = y_position;
	//right
	while (posx < 7)
		posx++, p[1].push_back(std::make_pair(posx, posy));
	//up
	posx = x_position, posy = y_position;
	while (posy > 0)
		posy--, p[2].push_back(std::make_pair(posx, posy));
	posx = x_position, posy = y_position;
	//down
	while (posy < 7)
		posy++, p[3].push_back(std::make_pair(posx, posy));
	return p;

}

void Rook::move(int x_next, int y_next)
{
	x_position = x_next;
	y_position = y_next;
	has_moved = true;
}
