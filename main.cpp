#include <iostream>
#include <vector>

#include "draw.cpp"
using namespace std;

int main(){
	Draw d;
	//Pieces p;
	//p.displayPieces();
	//Rules r;
	//std :: cout << r.isInCheck(0);
	//Pieces All;
	//All.displayPieces();

	/*

	std::vector<std::vector<std::pair<int, int>> > ans;
	ans = x.path();
	for (auto &w : ans){
		for (auto &it: w)
			std::cout << it.first << " " << it.second << " ";
	std::cout<<"\n";
	}
	*/
	Knight x(std::make_pair(6, 7),0);
	Rules R;
	std::vector<std::pair<int, int> > ans = R.getFuturePositions(&x);
	for (auto it:ans)
		std::cout << it.first <<" "<<it.second <<"\n";
	//std::vector<int *> v;
	//v.push_back(new int(4));
	//delete v[0];
    //cout << "Este sah "<< R.isInCheck(0) <<"\n";
	/*
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
	*/

    return 0;
}
