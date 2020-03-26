#include <iostream>
#include "piece.h"


int main(){

    Pawn p(1, 1, 0);
    std::cout << p.isValidPosition(1, 4);

    return 0;
}