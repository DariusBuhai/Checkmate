//
// Created by Darius Buhai on 3/27/20.
//

#ifndef CHECKMATE_TYPES_H
#define CHECKMATE_TYPES_H

#include "piece.h"

struct positionType{
    double x, y;

    positionType(double x = 0, double y = 0){
        this->x = x;
        this->y = y;
    }
};

struct sizeType{
    double width, height;
    sizeType(double width = 0, double height = 0){
        this->width = width;
        this->height = height;
    }
};

struct Move{
    Piece *piece = nullptr;
    Piece *deletedPiece = nullptr;
    Piece *updatedPiece = nullptr;
    std::pair<int, int> from, to;

    Move(Piece* p, std::pair<int, int> f, std::pair<int, int> t, Piece *dp = nullptr){
        this->piece = p;
        this->from = f;
        this->to = t;
        this->deletedPiece = dp;
    }
    Move(Piece* p, std::pair<int, int> t){
        this->piece = p;
        this->to = t;
    }
    Move(){
        piece = nullptr;
    }
};

struct Evaluation{
    int nr_pieces;
    int eval;
};
#endif //CHECKMATE_TYPES_H
