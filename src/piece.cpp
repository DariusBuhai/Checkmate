#include <iostream>
#include <vector>
#include <utility>

#include "../include/piece.h"
#include "../include/types.h"

// ------------- piece methods ----------------
Piece::Piece(std::pair<int, int> pos, int player) : pos(pos), has_moved(false), player(player) {}
Piece::Piece() : pos({0,0}), has_moved(false), player(0) {}

std::vector<std::vector<std::pair<int, int>>> Piece::path(){
    return std::vector<std::vector<std::pair<int,int>>>(0);
}

void Piece::move(std::pair<int, int> position){
    has_moved = true;
    pos = position;
}

std::string Piece::getType(){
    return this->type;
}

std::pair<int,int> Piece::getPos(){
    return this->pos;
}

int Piece::getPlayer(){
    return this->player;
}

bool Piece::getHasMoved(){
    return has_moved;
}

void Piece::set_position(int x_next, int y_next)
{
    pos.first = x_next;
    pos.second = y_next;
}


bool Piece::isInTable(std::pair<int, int> position)
{
    return ((position.first>= 0 && position.first<= 7) && (position.second>= 0 && position.second <= 7));
}

//--------------- Pawn methods -------------------

Pawn::Pawn(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){
    type = "Pawn";
}

std::vector<std::vector<std::pair<int, int> > > Pawn::path()
{
    std::vector<std::vector< std::pair<int,int > > > p;
    p.resize(3);
    int posx, posy;
    posx = pos.first;
    posy = pos.second;

    // we go down, we are black
    if (player == 1){
        posy++;
        if(isInTable({posx, posy}))
            p[0].emplace_back(std::make_pair(posx, posy));
        if(posy==2 && isInTable({posx, posy+1}))
            p[0].emplace_back(std::make_pair(posx, posy+1));
        posx++;
        if (isInTable({posx, posy}))
            p[1].push_back(std::make_pair(posx, posy));
        posx -= 2;
        if (Piece::isInTable({posx, posy}))
            p[2].push_back(std::make_pair(posx, posy));
    }
    // we go up, we are white
    else{
        posy--;
        if (isInTable({posx, posy}))
            p[0].emplace_back(std::make_pair(posx, posy));
        if (posy==5 && isInTable({posx, posy-1}))
            p[0].emplace_back(std::make_pair(posx, posy-1));
        posx++;
        if (isInTable({posx, posy}))
            p[1].push_back(std::make_pair(posx, posy));
        posx -= 2;
        if (isInTable({posx, posy}))
            p[2].push_back(std::make_pair(posx, posy));
    }
    return p;
}

//-------------- Rook Methods ----------------

Rook::Rook(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack)
{
    type = "Rook";
}

std::vector<std::vector<std::pair<int, int> > > Rook::path()
{
    std::vector<std::vector< std::pair<int, int > > > p;
    p.resize(4);
    //it can go up, down, left, right;
    //---- first we go up
    int posx, posy;
    posx = pos.first, posy = pos.second;
    //left
    while (posx > 0)
        posx--, p[0].push_back(std::make_pair(posx, posy));
    posx = pos.first, posy = pos.second;
    //right
    while (posx < 7)
        posx++, p[1].push_back(std::make_pair(posx, posy));
    //up
    posx = pos.first, posy = pos.second;
    while (posy > 0)
        posy--, p[2].push_back(std::make_pair(posx, posy));
    posx = pos.first, posy = pos.second;
    //down
    while (posy < 7)
        posy++, p[3].push_back(std::make_pair(posx, posy));
    return p;

}

// -------------- Knight Methods ------------------

Knight::Knight(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack)
{
    type = "Knight";
}

std::vector<std::vector<std::pair<int, int> > > Knight::path()
{
    std::vector<std::vector< std::pair<int, int > > > p;
    p.resize(8);
    int dist_x[] = { -2, -1, 2, 1, -2, -1, 2, 1 };
    int dist_y[] = { -1, -2, -1, -2, 1, 2, 1, 2 };
    for (int i = 0; i < 8; i++)
        if (Piece::isInTable({pos.first + dist_x[i], pos.second + dist_y[i]}))
            p[i].push_back(std::make_pair(pos.first + dist_x[i], pos.second + dist_y[i]));
    return p;

}

// ------------ Bishop Methods ---------------

Bishop::Bishop(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack){
    type = "Bishop";
}


std::vector<std::vector<std::pair<int, int> > > Bishop::path()
{
    std::vector<std::vector< std::pair<int, int > > > p;
    p.resize(4);
    int posx, posy;
    posx = pos.first,posy = pos.second;
    // up left
    while (Piece::isInTable({posx - 1, posy - 1}))
    {
        posx--, posy--, p[0].push_back(std::make_pair(posx, posy));
    }
    posx = pos.first, posy = pos.second;
    // up right
    while (Piece::isInTable({posx + 1, posy - 1}))
    {
        posx++, posy--, p[1].push_back(std::make_pair(posx, posy));
    }
    posx = pos.first, posy = pos.second;
    // down right
    while (Piece::isInTable({posx + 1, posy + 1}))
    {
        posx++, posy++, p[2].push_back(std::make_pair(posx, posy));
    }
    posx = pos.first, posy = pos.second;
    // down left
    while (Piece::isInTable({posx - 1, posy + 1}))
    {
        posx--, posy++, p[3].push_back(std::make_pair(posx, posy));
    }

    return p;

}

// ---------------- Queen Methods ----------------

Queen::Queen(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack)
{
    type = "Queen";
}


std::vector<std::vector<std::pair<int, int> > > Queen::path()
{
    std::vector<std::vector< std::pair<int, int > > > p;
    p.resize(8);
    int posx, posy;
    posx = pos.first, posy = pos.second;
    //left
    while (posx > 0)
        posx--, p[0].push_back(std::make_pair(posx, posy));
    posx = pos.first, posy = pos.second;
    //right
    while (posx < 7)
        posx++, p[1].push_back(std::make_pair(posx, posy));
    //up
    posx = pos.first, posy = pos.second;
    while (posy > 0)
        posy--, p[2].push_back(std::make_pair(posx, posy));
    posx = pos.first, posy = pos.second;
    //down
    while (posy < 7)
        posy++, p[3].push_back(std::make_pair(posx, posy));


    posx = pos.first, posy = pos.second;
    // up left
    while (Piece::isInTable({posx - 1, posy - 1}))
    {
        posx--, posy--, p[4].push_back(std::make_pair(posx, posy));
    }
    posx = pos.first, posy = pos.second;
    // up right
    while (Piece::isInTable({posx + 1, posy - 1}))
    {
        posx++, posy--, p[5].push_back(std::make_pair(posx, posy));
    }
    posx = pos.first, posy = pos.second;
    // down right
    while (Piece::isInTable({posx + 1, posy + 1}))
    {
        posx++, posy++, p[6].push_back(std::make_pair(posx, posy));
    }
    posx = pos.first, posy = pos.second;
    // down left
    while (Piece::isInTable({posx - 1, posy + 1}))
    {
        posx--, posy++, p[7].push_back(std::make_pair(posx, posy));
    }

    return p;
}

// ---------- King Methods -------------


King::King(std::pair<int,int> pos, bool isBlack) : Piece(pos, isBlack)
{
    type = "King";
}

std::vector<std::vector<std::pair<int, int> > > King::path()
{
    std::vector<std::vector< std::pair<int, int >>> p;
    p.resize(9);
    int dist_x[] = { 1, 1, 1, 0, -1, -1, -1, 0};
    int dist_y[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    for (int i = 0; i < 8; i++)
    {
        if (Piece::isInTable({pos.first + dist_x[i], pos.second + dist_y[i]}))
            p[i].push_back(std::make_pair(pos.first + dist_x[i], pos.second + dist_y[i]));
    }
    return p;
}