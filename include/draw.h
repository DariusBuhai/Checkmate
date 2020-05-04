//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_DRAW_H
#define CHECKMATE_DRAW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "../include/table.h"
#include "../include/materials.h"
#define ScreenWidth 1100
#define ScreenHeight 1100

class Draw{
private:

    const double screenWidth = ScreenWidth;
    const double screenHeight = ScreenHeight;

    Table table;

    bool darkMode = false;
    bool viewCredits = false;
    bool resetGameGulp = false;
    bool undoMoveGulp = false;
    bool playAgainstAi = false;

    Container<Button*> buttons;
    Container<Label*> labels;

    void draw(sf::RenderWindow*);
    void digestAction(sf::RenderWindow*, sf::Event);

    void init();
    void initComponents();

public:
    Draw();
    ~Draw();
    friend std::ostream& operator<<(std::ostream& , const Draw&);
};

#endif //CHECKMATE_DRAW_H
