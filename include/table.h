//
// Created by Darius Buhai on 3/26/20.
//

#include <SFML/Graphics.hpp>
#include "types.h"

#ifndef CHECKMATE_TABLE_H
#define CHECKMATE_TABLE_H

class Table{
private:
    const double margin = 14;
    const double padding = 5;
    const double border_width = 2;
public:
    void add_piece();
    void remove_piece(int hashcode);
    void draw(sf::RenderWindow*, encapsulation);
};

#endif //CHECKMATE_TABLE_H
