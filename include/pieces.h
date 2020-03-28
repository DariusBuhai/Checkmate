#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED
#include <vector>
#include <string>

#include "piece.h"

class Pieces{
private:
    std::vector <Piece> pieces;
public:

    Pieces();

    void displayPieces();
    void initPositions();

    std::vector <Piece> getPieces();
};

#endif // PIECES_H_INCLUDED
