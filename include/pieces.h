#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include <vector>
#include <deque>
#include <string>

/**
 * This is a subclass of rules! do not instanciate
 */

#include "piece.h"
#include "types.h"

class Pieces{
    void resizeBoard();
    void initPieces();
    void updateBoard();
protected:
    std::vector<std::vector<std::vector<Piece*>>> board;
    std::deque<Move> history;
    std::vector<Piece*> pieces;
    int currentPlayer = 0;
public:

    //std::vector<std::vector<std::vector<Piece*>>> board;
    Pieces();
    ~Pieces();

    std::vector<Piece* > getPieces();
    Piece* getPiece(int, std::pair<int, int>);
    Piece* operator[](std::pair<int, int>);
    std::vector<std::vector<Piece*>> operator[](int);

    void setPieces(const std::vector<Piece*>&);

    void movePiece(Piece*, std::pair<int, int>);
    void movePiece(std::pair<int, int>, std::pair<int, int>);

    int getCurrentPlayer();
    void setCurrentPlayer(int);
    void switchPlayer();

    void resetGame();
    void undoMove();
};


#endif // PIECES_H_INCLUDED
