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
    int player = 1;
    std::map<std::string, std::vector<std::vector<int>>> evaluation;

    int getBestRemoved(Piece*);
    int getEvaluation(Piece*, std::pair<int,int>);

public:
    Brain(Rules*);

    Move determineBestMove();
    void initializeEvaluation();
};

#endif //CHECKMATE_BRAIN_H
