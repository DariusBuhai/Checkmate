//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_DRAW_H
#define CHECKMATE_DRAW_H

#include <SFML/Graphics.hpp>
#include "../include/table.h"
#include "../include/pieces.h"
#include "../include/piece.h"

class Draw{
private:

    const double screen_width = 1000;
    const double screen_height = 1000;

    Table table;

    void draw(sf::RenderWindow*);

public:
    void init();
    Draw();
};


#endif //CHECKMATE_DRAW_H
