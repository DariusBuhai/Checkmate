//
// Created by Darius Buhai on 3/27/20.
//

#ifndef CHECKMATE_TYPES_H
#define CHECKMATE_TYPES_H

#include "piece.h"

struct position_type{
    double x, y;

    position_type(double x = 0, double y = 0){
        this->x = x;
        this->y = y;
    }
};

struct size_type{
    double width, height;
    size_type(double width = 0, double height = 0){
        this->width = width;
        this->height = height;
    }
};

struct Move{
    Piece *piece;
    std::pair<int, int> from, to;

    Move(Piece* p, std::pair<int, int> f, std::pair<int, int> t){
        this->piece = p;
        this->from = f;
        this->to = t;
    }
};
#endif //CHECKMATE_TYPES_H
