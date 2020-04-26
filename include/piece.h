//
// Created by Darius Buhai on 3/26/20.
//

#ifndef CHECKMATE_PIECE_H
#define CHECKMATE_PIECE_H
#include <vector>
#include <string>


class Piece{
protected:
    std::pair<int, int> pos;
    bool hasMoved;
    int player;

    void setPosition(int, int);
public:
    Piece(std::pair<int, int>, int);
    Piece();
    virtual ~Piece(){};
    bool isInTable(std::pair<int, int>);
    bool isInTable();

    std::pair<int,int> getPos();
    std::pair<int,int> getPosCastle();
    int getPlayer();
	bool getHasMoved();

    virtual std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    virtual std::string getType();
    void move(std::pair<int, int>);
    void resetHasMoved();

    virtual std::string getImage(int = 1);
};

class Pawn : public Piece
{
public:
    Pawn(Piece);
    Pawn(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    std::string getImage(int = 1);
    std::string getType();
};

class Rook : public Piece
{
public:
    Rook(Piece);
	Rook(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    std::string getImage(int = 1);
    std::string getType();
};

class Knight : public Piece
{
public:
    Knight(Piece);
	Knight(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    std::string getImage(int = 1);
    std::string getType();
};

class Bishop : public Piece
{
public:
    Bishop(Piece);
	Bishop(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    std::string getImage(int = 1);
    std::string getType();
};

class Queen : public Piece
{
public:
    Queen(Piece);
	Queen(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    std::string getImage(int = 1);
    std::string getType();
};


class King : public Piece
{
public:
    King(Piece);
	King(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>> >  path(std::pair<int,int>);
    std::string getImage(int = 1);
    std::string getType();
};

#endif //CHECKMATE_PIECE_H
