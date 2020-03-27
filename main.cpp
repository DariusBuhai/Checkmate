#include <iostream>

#include "include/draw.h"
#include "include/piece.h"

int main()
{

	Draw d;
	d.draw();
	Rook P(1, 1, 0);
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

    return 0;
}
