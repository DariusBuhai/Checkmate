//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_PIECE_H
#define CHECKMATE_PIECE_H
#include <vector>
#include <string>
#include "types.h"

class Piece{
public:
	bool isInTable(int, int);
protected:
    //int hashcode;
    std::pair<int, int> pos;
    std::string type;
    bool has_moved;
    bool is_black;
    //0 is for white, 1 is for black;
protected:
    Piece(std::pair<int, int>, bool);
    void set_position(int, int);

public:
    std::string getType();
    std::pair<int,int> getPos();
    bool getIsBlack();
};

class Pawn : public Piece
{
private:
	std::string name;
public:
    Pawn(std::pair<int, int>, bool);
	//for every piece we can have more ways path to take (for example the queen)
	//and for every path there are more squares that it can land on
    std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};

class Rook : public Piece
{
public:
	Rook(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);

};

class Knight : public Piece
{
public:
	Knight(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
    void move(int, int);
};

class Bishop : public Piece
{
public:
	Bishop(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};

class Queen : public Piece
{
public:
	Queen(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};


class King : public Piece
{
public:
	King(std::pair<int, int>, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};



#endif //CHECKMATE_PIECE_H
