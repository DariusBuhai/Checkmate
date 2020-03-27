//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_PIECE_H
#define CHECKMATE_PIECE_H
#include <vector>
#include <string>

class Piece{
protected:
    int hashcode;
    int x_position, y_position;
    bool has_moved;
    bool color;
    std::string name;
    //0 is for white, 1 is for black;
protected:
    static bool isInTable(int, int);
    Piece(int, int, bool);
    void set_position(int, int);
    
};

class Pawn : public Piece
{

public:
    Pawn(int, int, bool);
    //we are going to return a path of the piece to check later on the board if 
    //that position is reachable by the path  
    std::vector<std::pair<int, int>> path(int, int);
    //first we check if we can get there
    bool isValidPosition(int, int);


};
/*
class Rook : public Piece
{
public:
    void move(int, int, int);

};

class Knight : public Piece
{
public:
    void move(int, int, int);
};

class Bishop : public Piece
{
public:
    void move(int, int, int);
};

class Queen : public Piece
{
public:
    void move(int, int, int);
};

class King : public Piece
{
public:
    void move(int, int, int);
};

*/

#endif //CHECKMATE_PIECE_H
