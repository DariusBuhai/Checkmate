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

    SizeType size;
    std::pair<int,int> position;

    std::pair<int, int> selectedSquare = {-1, -1};
    std::pair<int, int> selectedPieceCurrentLocation = {-1,-1};
    Piece* selectedPiece = nullptr;
    std::vector<std::pair<int, int>> futurePositions;

    bool mouseButtonPressing = false;

    bool playAgainstAi = false;
    bool darkMode = false;
    bool checkMate = false;
    int winnerPlayer = -1;

    Rules rules;
    Brain* brain;

    sf::Clock gameClock;

    void resetFuturePositions();
    void resetSelectedPieceLocation();
    void resetSelectedSquare();

    void updateSelectedSquare(std::pair<int, int>);

    bool isInsideTable(std::pair<int,int>) const;
    void drawGrid(sf::RenderWindow*, SizeType, std::pair<int,int>);
    void drawOutline(sf::RenderWindow*, SizeType, std::pair<int,int>) const;
    void drawIndicators(sf::RenderWindow*, SizeType, std::pair<int,int>) const;

    std::pair<int, int> determineGridPosition(std::pair<int,int>) const;

public:
    Table();
    ~Table();

    void digestAction(sf::Event);

    void draw(sf::RenderWindow*);
    void drawPiece(sf::RenderWindow*, Piece*) const;

    void setSize(SizeType);
    void setPosition(std::pair<int,int>);
    void setDarkMode(bool);

    bool getIsCheckMate() const;
    int getWinnerPlayer() const;

    void resetGame();
    void undoMove();
    void togglePlayAgainstAi();

    bool isPlayingAgainstAi() const;
};

#endif //CHECKMATE_TABLE_H
