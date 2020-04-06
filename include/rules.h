#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED
#include "piece.h"
#include "pieces.h"
#include <string>
#include <vector>

/*
to do -
a function that gets you a list of location that your piece can attack
a function that checks if you are in check based on the up function
a function that determines where can you move a piece based on the upper functions
a function that gets a list of all possible moves for you 
*/

#include "pieces.h"

class Rules: public Pieces
{
private:

    inline void save_board(Piece[2][9][9]);
    inline void get_board(Piece[2][9][9]);

public:
    //tells you what piece is on the field
    std::vector <std::pair<int, int>> canAttackPos(std::pair<int, int>, int);
    bool isInCheck(int);
    std::vector<std::pair<int, int> > getPositions(Piece, int);

};



#endif