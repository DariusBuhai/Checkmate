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
    bool has_moved;
    int player;

    void setPosition(int, int);
public:

    Piece(std::pair<int, int>, int);
    Piece();
    virtual ~Piece(){};
    static bool isInTable(std::pair<int, int>);

    std::pair<int,int> getPos();
    int getPlayer();
	bool getHasMoved();

    virtual std::vector<std::vector<std::pair<int, int>>> path();
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
};

class Rook : public Piece
{
public:
	Rook(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
};

class Knight : public Piece
{
public:
	Knight(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
};

class Bishop : public Piece
{
public:
	Bishop(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
};

class Queen : public Piece
{
public:
	Queen(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
};


class King : public Piece
{
public:
	King(std::pair<int, int>, bool);
    std::vector<std::vector<std::pair<int, int>>> path();
    std::string getImage();
};

#endif //CHECKMATE_PIECE_H
