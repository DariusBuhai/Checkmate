//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_DRAW_H
#define CHECKMATE_DRAW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../include/table.h"

class Draw{
private:

    const double screenWidth = 1100;
    const double screenHeight = 1100;

    Table table;

    bool hoveringResetButton = false;
    bool hoveringPreviousMoveButton = false;
    bool hoveringPlayAiButton = false;
    bool hoveringDarkModeButton = false;
    bool darkMode = false;

    bool mouseInsideLimits(std::pair<int, int>, std::pair<int, int>, std::pair<int,int>);
    bool mouseInsideLimits(sf::Event, std::pair<int, int>, std::pair<int,int>);

    void draw(sf::RenderWindow*);
    void digestAction(sf::RenderWindow*, sf::Event);

    void drawText(sf::RenderWindow*, std::string, sf::Color, std::pair<int, int>, int = 40);

public:
    void init();
    Draw();
};


#endif //CHECKMATE_DRAW_H
