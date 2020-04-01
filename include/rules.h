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

class Rules
{
private:

    //board[i][j][0] keeps the pieces of the white player, 1 is for black
    std::string board[9][9][2];
    std::vector <Piece> pieces;

public:
    //a list of position the piece attacks
    Rules(std::vector <Piece>);
    //tells you what piece is on the field
    std::vector <std::pair<int, int> > canAttackPos(std::pair<int, int>, bool); 
    bool isInCheck(bool);
    std::vector<std::pair<int, int> > getPositions(std::pair<int, int>, bool);

};



#endif