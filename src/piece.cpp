#include <iostream>
#include <vector>
#include <utility>

#include "../include/piece.h"


// ------------- piece methods ----------------
Piece::Piece(int x_position, int y_position, bool color) : x_position(x_position), 
y_position(y_position), has_moved(false), color(color){}

void Piece::set_position(int x_next, int y_next)
{
    x_position = x_next;
    y_position = y_next;
}
bool Piece::isInTable(int x, int y)
{
    return ((x>= 0 && x<= 7) && (y>= 0 && y <= 7));
}

//--------------- Pawn methods -------------------

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


std::vector<std::vector<std::pair<int, int> > > Pawn::path()
{
    std::vector<std::vector< std::pair<int,int > > > p;
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

//-------------- Rook Methods ----------------

Rook::Rook(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
	name = "Rook";
}

std::vector<std::vector<std::pair<int, int> > > Rook::path()
{
	std::vector<std::vector< std::pair<int, int > > > p;
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


// -------------- Knight Methods ------------------

Knight::Knight(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
	name = "Rook";
}

std::vector<std::vector<std::pair<int, int> > > Knight::path()
{
	std::vector<std::vector< std::pair<int, int > > > p;
	p.resize(8);
	int dist_x[] = { -2, -1, 2, 1, -2, -1, 2, 1 };
	int dist_y[] = { -1, -2, -1, -2, 1, 2, 1, 2 };
	for (int i = 0; i < 8; i++)
	{

		if (Pawn::isInTable(x_position + dist_x[i], y_position + dist_y[i]))
			p[i].push_back(std::make_pair(x_position + dist_x[i], y_position + dist_y[i]));
	}
	return p;

}
void Knight::move(int x_next, int y_next)
{
	has_moved = true;
	x_position = x_next;
	y_position = y_next;
}

// ------------ Bishop Methods ---------------

Bishop::Bishop(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
	name = "Bishop";
}


std::vector<std::vector<std::pair<int, int> > > Bishop::path()
{
	std::vector<std::vector< std::pair<int, int > > > p;
	p.resize(4);
	int posx, posy;
	posx = x_position,posy = y_position;
	// up left
	while (Pawn::isInTable(posx - 1, posy - 1))
	{
		posx--, posy--, p[0].push_back(std::make_pair(posx, posy));
	}
	posx = x_position, posy = y_position;
	// up right
	while (Pawn::isInTable(posx + 1, posy - 1))
	{
		posx++, posy--, p[1].push_back(std::make_pair(posx, posy));
	}
	posx = x_position, posy = y_position;
	// down right
	while (Pawn::isInTable(posx + 1, posy + 1))
	{
		posx++, posy++, p[2].push_back(std::make_pair(posx, posy));
	}
	posx = x_position, posy = y_position;
	// down left
	while (Pawn::isInTable(posx - 1, posy + 1))
	{
		posx--, posy++, p[3].push_back(std::make_pair(posx, posy));
	}

	return p;

}

void Bishop::move(int x_next, int y_next)
{
	has_moved = true;
	x_position = x_next;
	y_position = y_next;
}

// ---------------- Queen Methods ----------------

Queen::Queen(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
	name = "Queen";
}


std::vector<std::vector<std::pair<int, int> > > Queen::path()
{
	std::vector<std::vector< std::pair<int, int > > > p;
	p.resize(8);
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


	posx = x_position, posy = y_position;
	// up left
	while (Pawn::isInTable(posx - 1, posy - 1))
	{
		posx--, posy--, p[4].push_back(std::make_pair(posx, posy));
	}
	posx = x_position, posy = y_position;
	// up right
	while (Pawn::isInTable(posx + 1, posy - 1))
	{
		posx++, posy--, p[5].push_back(std::make_pair(posx, posy));
	}
	posx = x_position, posy = y_position;
	// down right
	while (Pawn::isInTable(posx + 1, posy + 1))
	{
		posx++, posy++, p[6].push_back(std::make_pair(posx, posy));
	}
	posx = x_position, posy = y_position;
	// down left
	while (Pawn::isInTable(posx - 1, posy + 1))
	{
		posx--, posy++, p[7].push_back(std::make_pair(posx, posy));
	}

	return p;
}

void Queen::move(int x_next, int y_next)
{
	has_moved = true;
	x_position = x_next;
	y_position = y_next;
}


// ---------- King Methods -------------


King::King(int x_position, int y_position, bool color) : Piece(x_position, y_position, color)
{
	name = "King";
}

std::vector<std::vector<std::pair<int, int> > > King::path()
{
	std::vector<std::vector< std::pair<int, int > > > p;
	p.resize(9);
	int dist_x[] = { 1, 1, 1, 0, -1, -1, -1, 0};
	int dist_y[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int posx, posy;
	for (int i = 0; i < 8; i++)
	{
		if (Pawn::isInTable(x_position + dist_x[i], y_position + dist_y[i]))
			 p[i].push_back(std::make_pair(x_position + dist_x[i], y_position + dist_y[i]));
	}
	return p;
}


void King::move(int x_next, int y_next)
{
	has_moved = true;
	x_position = x_next;
	y_position = y_next;
}