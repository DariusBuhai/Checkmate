//
// Created by Darius Buhai on 4/10/20.
//

#include "../include/brain.h"
#include "../include/rules.h"
#include "../include/piece.h"
#include "../include/types.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

Brain::Brain(Rules* r){
    rules = r;
}

int Brain::getEvaluation(Piece* piece) {
    if (dynamic_cast<Pawn *>(piece))
        return 10;
    if (dynamic_cast<Knight *>(piece))
        return 30;
    if (dynamic_cast<Bishop *>(piece))
        return 30;
    if (dynamic_cast<Rook *>(piece))
        return 50;
    if (dynamic_cast<Queen *>(piece))
        return 90;
    if (dynamic_cast<King *>(piece))
        return 900;
    return 0;
}


Move Brain::determineBestMove(){
    if(rules == nullptr) throw EXIT_FAILURE;

    vector<Move> future_pos;
    Move best_move;
    int best_eval = -9999;

    for(Piece* piece: rules->getPieces()){
        for(auto pos: rules->getFuturePositions(piece)){
            cout<<pos.first<<' '<<pos.second<<'\n';
            Piece* opPlayer = rules->getPiece(piece->getPlayer(), pos);
            future_pos.emplace_back(Move(piece, pos));
            if(opPlayer!= nullptr){
                int eval = getEvaluation(opPlayer);
                if(eval>best_eval){
                    best_eval = eval;
                    best_move = Move(piece, pos);
                }
            }
        }
    }

    if(best_move.piece!= nullptr)
        return best_move;
    return future_pos[random() % future_pos.size()];
}

