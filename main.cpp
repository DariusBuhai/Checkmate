#include <iostream>

#include "include/draw.h"
#include "include/piece.h"
#include "include/table.h"
//#include "draw.cpp"
//#include "piece.cpp"

int main()
{

	Draw d;
	d.draw();
	King P(1, 1, false);
	/*std::vector<std::vector< std::pair<int, int > > > p;
	p = P.path();
	for (auto way : p)
	{
		for (auto pos : way)
		{
			std::cout << pos.first << " " << pos.second << "\n";
		}
		std::cout << "\n";

	}*/
    return 0;
}
