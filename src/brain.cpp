//
// Created by Darius Buhai on 4/10/20.
//

#include "../include/brain.h"
#include "../include/rules.h"
#include "../include/piece.h"
#include "../include/types.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

Brain::Brain(Rules* r){
    rules = r;
    initializeEvaluation();
}

void Brain::initializeEvaluation(){
    vector<string> pt = {"pawn", "bishop", "knight", "queen", "rook", "king"};
    for(auto p: pt){
        ifstream read("data/evaluation/"+p+".txt");
        int x;
        evaluation[p].resize(8);
        for(int i=0;i<8;i++)
            for (int j = 0; j < 8; j++){
                read>>x;
                evaluation[p][i].push_back(x);
            }
        read.close();
    }
}

int Brain::getBestRemoved(Piece* piece) {
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

int Brain::getEvaluation(Piece* piece, pair<int,int> pos){
    if(player==1)
        return evaluation[piece->getType()][pos.first][pos.second];
    return evaluation[piece->getType()][7-pos.first][7-pos.second];
}

Move Brain::determineBestMove(){
    if(rules == nullptr) throw EXIT_FAILURE;

    vector<Move> future_pos;

    Move best_eval_move;
    int best_eval = -9999;

    Move best_removed_move;
    int best_removed = -9999;

    for(Piece* piece: rules->getPieces()){
        for(auto pos: rules->getFuturePositions(piece)){
            Piece* opPlayer = rules->getPiece(!piece->getPlayer(), pos);
            future_pos.emplace_back(Move(piece, pos));

            int eval = this->getEvaluation(piece, pos) * 10;
            if(eval > best_eval){
                best_eval = eval;
                best_eval_move = Move(piece, pos);
            }

            if(opPlayer != nullptr){
                int eval = getBestRemoved(opPlayer);
                if(eval>best_removed){
                    best_removed = eval;
                    best_removed_move = Move(piece, pos);
                }
            }
        }
    }
    if(future_pos.empty()) {
        cout << "No moves found! Checkmate\n";
        return Move();
    }
    if(best_removed_move.piece != nullptr){
        cout<<"Found the best piece to remove\n";
        return best_removed_move;
    }
    if(best_eval_move.piece!= nullptr){
        cout<<"Moving based on evaluation\n";
        return best_eval_move;
    }
    cout << "Moving to a random position\n";
    return future_pos[random() % future_pos.size()];
}

