//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_PIECE_H
#define CHECKMATE_PIECE_H
#include <vector>
#include <string>

#include "types.h"

class Piece{
protected:
    std::pair<int, int> pos;
    std::string type;
    bool has_moved;
    bool is_black;

    void set_position(int, int);
public:

    Piece(std::pair<int, int>, bool);
    Piece();

    bool isInTable(std::pair<int, int>);

    std::string getType();
    std::pair<int,int> getPos();
    bool getIsBlack();
	bool getHasMoved();

    virtual std::vector<std::vector<std::pair<int, int>>> path();
    void move(std::pair<int, int>);
};

class Pawn : public Piece
{
private:
	std::string name;
public:
    Pawn(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
};

class Rook : public Piece
{
public:
	Rook(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int>>> path();
};

class Knight : public Piece
{
public:
	Knight(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int>>> path();
};

class Bishop : public Piece
{
public:
	Bishop(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int>>> path();
};

class Queen : public Piece
{
public:
	Queen(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int>>> path();
};


class King : public Piece
{
public:
	King(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int>>> path();
};

#endif //CHECKMATE_PIECE_H
