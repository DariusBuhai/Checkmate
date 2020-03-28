//
// Created by Darius Buhai on 3/26/20.
//

#include <SFML/Graphics.hpp>

#include <vector>

#include "types.h"
#include "piece.h"

#ifndef CHECKMATE_TABLE_H
#define CHECKMATE_TABLE_H

class Table{
private:
    /// Settings
    const double padding = 10;
    const double border_width = 10;
    const double indicator_spacing = 100;

    std::vector<std::vector<bool> > selected_squares;

    size_type size;
    position_type position;

    void resetSelectedSquares();

    void draw_grid(sf::RenderWindow*, size_type, position_type);
    void draw_outline(sf::RenderWindow*, size_type, position_type);
    void draw_indicators(sf::RenderWindow*, size_type, position_type);

    std::pair<int, int> determine_grid_position(position_type);

public:

    Table();

    void digest_action(position_type);

    void draw_piece(sf::RenderWindow*, Piece);

    void draw(sf::RenderWindow*);

    void setSize(size_type s);
    void setPosition(position_type p);
};

#endif //CHECKMATE_TABLE_H
