#include <iostream>
#include <vector>

#include "include/draw.h"
#include "include/piece.h"
#include "include/pieces.h"
#include "include/rules.h"

using namespace std;

int main(){
	//Draw d;

	Pieces All;
	//All.displayPieces();
    Rules R;
    //cout << "Este sah "<< R.isInCheck(0) <<"\n";

	std::vector<std::pair<int, int>> vec;
	vec = R.canAttackPos(std::make_pair(3, 2), 0);
	for (auto it:vec)
		std::cout << it.first <<" "<<it.second <<"\n";


	Knight P({3, 2}, false);
	std::vector<std::vector< std::pair<int, int > > > p;
	p = P.path();
	for (auto way : p){
		for (auto pos : way){
			std::cout << pos.first << " " << pos.second;
		}
		std::cout << "\n";
	}
	
    return 0;
}
