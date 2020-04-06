#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED
#include <vector>
#include <string>

#include "piece.h"

class Pieces{
private:
    void initPieces();
    void initBoard();
protected:
    Piece *board[2][8][8];
    std::vector<Piece> pieces;
public:

    Pieces();
    void displayPieces();
    std::vector<Piece> getPieces();
    Piece* getPiece(std::pair<int, int>);
    void setPieces(std::vector<Piece>);
    ~Pieces();
};


#endif // PIECES_H_INCLUDED
