//
// Created by Darius Buhai on 3/26/20.
//

#include <SFML/Graphics.hpp>
#include "types.h"

#ifndef CHECKMATE_TABLE_H
#define CHECKMATE_TABLE_H

class Table{
private:
    const double padding = 10;
    const double border_width = 10;
    const double indicator_spacing = 100;

    size_type size;
    position_type position;

    void draw_grid(sf::RenderWindow*, size_type, position_type);
    void draw_outline(sf::RenderWindow*, size_type, position_type);
    void draw_indicators(sf::RenderWindow*, size_type, position_type);
public:
    std::pair<size_type, position_type> get_piece_position(int i, int j);

    void draw(sf::RenderWindow*);

    void setSize(size_type s);
    void setPosition(position_type p);
};

#endif //CHECKMATE_TABLE_H
