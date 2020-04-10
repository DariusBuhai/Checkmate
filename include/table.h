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
    const double borderWidth = 10;
    const double indicatorSpacing = 100;

    size_type size;
    position_type position;

    std::pair<int, int> selectedSquare = {-1, -1};
    std::vector<std::pair<int, int>> futurePositions;
    Piece* lastSelectedPiece = nullptr;

    bool playAgainstAi = false;
    bool darkMode = false;

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

    void setSize(size_type);
    void setPosition(position_type);
    void setDarkMode(bool);

    void resetGame();
    void undoMove();
    void togglePlayAgainstAi();

    bool isPlayingAgainstAi() const;
};

#endif //CHECKMATE_TABLE_H
