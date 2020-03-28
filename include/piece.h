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
    //int hashcode;
    int x_position, y_position;
    bool has_moved;
    std :: string type;
    bool color;
    //0 is for white, 1 is for black;
protected:
    bool isInTable(int, int);
    Piece(int, int, bool);
    void set_position(int, int);
};

class Pawn : public Piece
{
private:
	std::string name;
public:
    Pawn(int, int, bool);
	//for every piece we can have more ways path to take (for example the queen)
	//and for every path there are more squares that it can land on
    std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);


};

class Rook : public Piece
{
private:
	std::string name;
public:
	Rook(int, int, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);

};

class Knight : public Piece
{
private:
	std::string name;
public:
	Knight(int, int, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
    void move(int, int);
};

class Bishop : public Piece
{
private:
	std::string name;
public:
	Bishop(int, int, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};

class Queen : public Piece
{
private:
	std::string name;
public:
	Queen(int, int, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};


class King : public Piece
{
private:
	std::string name;
public:
	King(int, int, bool);
	std::vector<std::vector<std::pair<int, int> > > path();
	void move(int, int);
};



#endif //CHECKMATE_PIECE_H
