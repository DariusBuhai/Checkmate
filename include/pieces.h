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
    void initPieces();
    void updateBoard();
protected:
    Piece* board[2][8][8];
    std::deque<Move> history;
    std::vector<Piece *> pieces;
    int current_player;
public:

    Pieces();
    ~Pieces();

    std::vector<Piece* > getPieces();
    Piece* getPiece(std::pair<int, int>);
    Piece* getPiece(std::pair<int, int>, int);

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
