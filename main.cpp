#include <iostream>
#include "piece.h"
#include "draw.h"

int main()
{
    std::cout<<1;
    Draw d;
    d.draw();
    Pawn p(1, 1, 0);
    std::cout << p.isValidPosition(1, 4);
    return 0;
}
