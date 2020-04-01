#include <iostream>
#include <vector>

#include "include/draw.h"
#include "include/piece.h"
#include "include/pieces.h"
#include "include/rules.h"

int main()
{
	
	//Draw d;
	
	
	
	Pieces All;
	All.initPositions();
	//All.displayPieces();
	Rules R(All.getPieces());
	std::cout << "Este sah "<< R.isInCheck(1) <<"\n";
	/*
	std::vector<std::pair<int, int>> vec;
	vec = R.canAttackPos(std::make_pair(3, 2), 0);
	for (auto it:vec)
		std::cout << it.first <<" "<<it.second <<"\n";
	*/
	/*
	Knight P({3, 2}, false);
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
	*/
	
    return 0;
}
