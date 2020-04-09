//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_DRAW_H
#define CHECKMATE_DRAW_H

#include <SFML/Graphics.hpp>

#include "../include/table.h"

class Draw{
private:

    const double screen_width = 1100;
    const double screen_height = 1100;

    Table table;

    void draw(sf::RenderWindow*);
    void digestAction(sf::Event);

    void drawButton(sf::RenderWindow*, std::string, sf::Color, std::pair<int, int>);

public:
    void init();
    Draw();
};


#endif //CHECKMATE_DRAW_H
