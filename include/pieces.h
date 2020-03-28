#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED
#include <vector>
#include <string>
#include "types.h"


class Pieces{
public:
    std :: vector < pieces_pos_type > pieces_positions;
public:
    //vector cu pozitiile piselor
    void init_pieces_positions();
    void get_pieces_positions();
    //functie ce returneaza pozitia piseleor si tipul lor
};

#endif // PIECES_H_INCLUDED
