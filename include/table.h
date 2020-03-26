//
// Created by Darius Buhai on 3/26/20.
//

#include <SFML/Graphics.hpp>

#ifndef CHECKMATE_TABLE_H
#define CHECKMATE_TABLE_H

class Table{
private:

public:
    void add_piece();
    sf::RectangleShape getVisual();
};

#endif //CHECKMATE_TABLE_H
