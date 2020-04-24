//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_DRAW_H
#define CHECKMATE_DRAW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "../include/table.h"
#include "../include/materials.h"

class Draw{
private:

    const double screenWidth = 1100;
    const double screenHeight = 1100;

    Table table;

    bool darkMode = false;
    bool viewCredits = false;
    bool resetGameGulp = false;
    bool undoMoveGulp = false;
    bool playAgainstAi = false;

    Container<Button*> buttons;

    void draw(sf::RenderWindow*);
    void digestAction(sf::RenderWindow*, sf::Event);

    void init();
    void initComponents();

public:
    Draw();
};

#endif //CHECKMATE_DRAW_H
