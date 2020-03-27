//
// Created by Darius Buhai on 3/27/20.
//

#ifndef CHECKMATE_TYPES_H
#define CHECKMATE_TYPES_H

struct encapsulation{
    double width, height;
    double x, y;

    encapsulation(double width, double height, double x = 0, double y = 0){
        this->width = width;
        this->height = height;
        this->x = x;
        this->y = y;
    }
};

#endif //CHECKMATE_TYPES_H
