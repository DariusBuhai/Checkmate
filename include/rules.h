#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include <string>
#include <vector>

#include "piece.h"
#include "pieces.h"

/**
 *
to do -
a function that gets you a list of location that your piece can attack
a function that checks if you are in check based on the up function
a function that determines where can you move a piece based on the upper functions
a function that gets a list of all possible moves for you 
*/

class Rules: public Pieces{
private:
    inline void saveBoard(Piece* [2][8][8]);
    inline void getBoard(Piece* [2][8][8]);

    bool play_against_ai = false;
public:
    Rules();
    ~Rules();
    void helper();
    std::vector <std::pair<int, int>> canAttackPos(Piece*);
    bool isInCheck(int);
    std::vector<std::pair<int, int>> getFuturePositions(Piece*);
    std::vector<std::pair<int, int>> getFuturePawn(Piece*);
    void togglePlayAgainstAi();
};

#endif