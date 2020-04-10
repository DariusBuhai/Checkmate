//
// Created by Darius Buhai on 4/10/20.
//

#ifndef CHECKMATE_BRAIN_H
#define CHECKMATE_BRAIN_H

#include <map>

#include "rules.h"
#include "piece.h"

class Brain{
private:
    Rules* rules;
    int player = 0;

    int getEvaluation(Piece*);
public:
    Brain(Rules*);
    Move determineBestMove();
};

#endif //CHECKMATE_BRAIN_H
