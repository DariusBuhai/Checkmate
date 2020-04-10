//
// Created by Darius Buhai on 3/26/20.
//

#include <SFML/Graphics.hpp>

#include <vector>

#include "types.h"
#include "piece.h"
#include "rules.h"
#include "brain.h"

#ifndef CHECKMATE_TABLE_H
#define CHECKMATE_TABLE_H

class Table{
private:
    /// Settings
    const double padding = 10;
    const double border_width = 10;
    const double indicator_spacing = 100;

    size_type size;
    position_type position;

    std::pair<int, int> selected_square = {-1, -1};
    std::vector<std::pair<int, int>> future_positions;
    Piece* last_selected_piece = nullptr;
    bool play_against_ai = false;

    Rules rules;
    Brain* brain;

    void resetFuturePositions();

    void resetSelectedSquare();
    void updateSelectedSquare(std::pair<int, int>);

    void drawGrid(sf::RenderWindow*, size_type, position_type);
    void drawOutline(sf::RenderWindow*, size_type, position_type);
    void drawIndicators(sf::RenderWindow*, size_type, position_type);

    std::pair<int, int> determine_grid_position(position_type);

public:
    Table();
    ~Table();

    void digestAction(sf::Event);

    void draw(sf::RenderWindow*);
    void drawPiece(sf::RenderWindow*, Piece*);

    void setSize(size_type s);
    void setPosition(position_type p);

    void resetGame();
    void undoMove();
    void togglePlayAgainstAi();

    bool isPlayingAgainstAi() const;
};

#endif //CHECKMATE_TABLE_H
