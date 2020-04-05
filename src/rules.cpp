#include "../include/rules.h"
#include "../include/piece.h"
#include <string>
#include <vector>
#include <iostream>

Rules::Rules(std::vector<Piece> items)
{
    piece_list.clear();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j][0] = "", board[i][j][1] = "";

    for (auto it : items)
        board[it.getPos().first][it.getPos().second][it.getIsBlack()] =
        it.getType(), piece_list.push_back(it);
    
/*
    std::cout<<"culoarea alba\n";
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            std::cout<< i<<" "<<j<<" "<<board[j][i][0]<<"\n";


    std::cout<<"culoare neagra\n";
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            std::cout<< i<<" "<<j<<" "<<board[j][i][1]<<"\n";
*/

}


std::vector <std::pair<int, int> > Rules::canAttackPos(std::pair<int, int> pos, bool type)
{
    std::vector<std::pair<int, int> > ans;
    std::vector<std::vector<std::pair<int, int> > > path;
    //if (board[pos.first][pos.second][type] == "Pawn")
    if (board[pos.first][pos.second][type] == "Pawn")
    {
        Pawn temp(std::make_pair(pos.first, pos.second), type);
        path = temp.path();
    }
    if (board[pos.first][pos.second][type] == "Rook")
    {
        Rook temp(std::make_pair(pos.first, pos.second), type);
        path = temp.path();
    }
    if (board[pos.first][pos.second][type] == "Knight")
    {
        Knight temp(std::make_pair(pos.first, pos.second), type);
        path = temp.path();
    }
    if (board[pos.first][pos.second][type] == "Queen")
    {
        Queen temp(std::make_pair(pos.first, pos.second), type);
        path = temp.path();
    }
    if (board[pos.first][pos.second][type] == "Bishop")
    {
        Bishop temp(std::make_pair(pos.first, pos.second), type);
        path = temp.path();
    }
    if (board[pos.first][pos.second][type] == "King")
    {
        King temp(std::make_pair(pos.first, pos.second), type);
        path = temp.path();
    }
    for (auto way : path)
        for (auto p : way)
        {
            if (board[p.first][p.second][type].size())
                break;
            ans.push_back(std::make_pair(p.first, p.second));
            if (board[p.first][p.second][!type].size())
                break;
        }
    return ans;
}

bool Rules::isInCheck(bool color)
{
    bool mat[9][9];
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j][!color].size())
                {
                    pos = canAttackPos(std::make_pair(i,j), !color);
                    for (auto it:pos)
                        mat[it.first][it.second] = 1;
                    pos.clear();
                }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j][color] == "King")
                return mat[i][j];
    return 0;
}

inline void Rules:: save_board(std::string aux_board[9][9][2])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 2; k++)
                aux_board[i][j][k] = board[i][j][k];
}


inline void Rules:: get_board(std::string aux_board[9][9][2])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 2; k++)
                board[i][j][k] = aux_board[i][j][k];
}


std::vector<std::pair<int, int>> Rules::getPositions(Piece pcs, bool type)
{
    std::string aux_board[9][9][2];
    std::pair<int, int> pos = pcs.getPos();
    std::vector<std::pair<int, int>> ans;
    std::vector<std::pair<int, int>> location;

    save_board(aux_board);
    if (board[pos.first][pos.second][type] == "Pawn") {
        //pawn can move back and front, but can only attack sideways, so we are gonna check
        //if we can move up and down first

        int dst = 1;
        //to keep track where we going
        if (type == 0) {
            dst = -1;
        }
        if (!board[pos.first][pos.second + dst][0].size() and !board[pos.first][pos.second + dst][1].size()) {
            board[pos.first][pos.second + dst][type] = "Pawn";
            board[pos.first][pos.second + dst][!type] = "";
            board[pos.first][pos.second + dst][type] = "";
            if (!isInCheck(type))
                ans.push_back(std::make_pair(pos.first, pos.second + dst));
            get_board(aux_board);
            if (!pcs.getHasMoved()) {
                dst *= 2;
                if (!board[pos.first][pos.second + dst][0].size() and !board[pos.first][pos.second + dst][1].size()) {
                    save_board(aux_board);
                    board[pos.first][pos.second + dst][type] = "Pawn";
                    board[pos.first][pos.second + dst][!type] = "";
                    board[pos.first][pos.second + dst][type] = "";
                    if (!isInCheck(0))
                        ans.push_back(std::make_pair(pos.first, pos.second + dst));
                }
                get_board(aux_board);
            }
        }
        location = this->canAttackPos(pos, type);
        for (auto it:location) {
            board[it.first][it.second][type] = board[pos.first][pos.second][type];
            board[it.first][it.second][!type] = "";
            board[pos.first][pos.second][type] = "";
            if (!isInCheck(type))
                ans.push_back(it);
            get_board(aux_board);
        }
    }
    // we are  going to check all the positions we can attack
}
