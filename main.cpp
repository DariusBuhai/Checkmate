#include <iostream>
#include <vector>

#include "include/draw.h"
#include "include/piece.h"
#include "include/pieces.h"
#include "include/rules.h"

int main()
{
	/*
	Draw d;
	*/
	
	
	Pieces All;
	All.initPositions();
	All.displayPieces();
	std::vector<Piece> v = All.getPieces();


	King P({1, 1}, false);
	std::vector<std::vector< std::pair<int, int > > > p;
	p = P.path();
	for (auto way : p)
	{
		for (auto pos : way)
		{
			std::cout << pos.first << " " << pos.second << "\n";
		}
		std::cout << "\n";
	}
    return 0;
}
