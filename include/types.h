//
// Created by Darius Buhai on 3/27/20.
//

#ifndef CHECKMATE_TYPES_H
#define CHECKMATE_TYPES_H

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

#endif //CHECKMATE_TYPES_H
