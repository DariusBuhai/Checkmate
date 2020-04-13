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
    int getPlayer();
	bool getHasMoved();

    virtual std::vector<std::vector<std::pair<int, int>>> path();
    virtual std::string getType();
    void move(std::pair<int, int>);
    void resetHasMoved();

    virtual std::string getImage();
};

class Pawn : public Piece
{
public:
    Pawn(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
    std::string getType();
};

class Rook : public Piece
{
public:
	Rook(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
    std::string getType();
};

class Knight : public Piece
{
public:
	Knight(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
    std::string getType();
};

class Bishop : public Piece
{
public:
	Bishop(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
    std::string getType();
};

class Queen : public Piece
{
public:
	Queen(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
    std::string getType();
};


class King : public Piece
{
public:
	King(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
    std::string getType();
};

#endif //CHECKMATE_PIECE_H
