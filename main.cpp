#include <iostream>

#include "include/draw.h"
#include "include/piece.h"
#include "include/table.h"
#include "include/pieces.h"
#include "draw.cpp"
#include "piece.cpp"
#include "pieces.cpp"

int main()
{

	Draw d;
	d.draw();
	Pieces All;
	All.init_pieces_positions();
	All.get_pieces_positions();
	/*King P(1, 1, 0);
	std::vector<std::vector< std::pair<int, int >>> p;
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
