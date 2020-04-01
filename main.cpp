#include <iostream>

#include "include/draw.h"
#include "include/piece.h"
#include "include/pieces.h"


int main()
{

	Draw d;
	Pieces All;
	All.initPositions();
	All.displayPieces();
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
