#include "../include/rules.h"
#include "../include/piece.h"
#include <string>
#include <vector>
#include <iostream>

Rules::Rules(std::vector<Piece> items)
{
    pieces.clear();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j][0] = "", board[i][j][1] = "";

    for (auto it : items)
        board[it.getPos().first][it.getPos().second][it.getIsBlack()] =
        it.getType();
    
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
    for (int i = 0; i < 9; i++)
        for (int j = 0 ; j < 9; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j][!color].size())
                {
                    pos = canAttackPos(std::make_pair(i,j), !color);
                    for (auto it:pos)
                        mat[it.first][it.second] = 1;
                    pos.clear();
                }
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j][color] == "King")
                return mat[i][j];
    return 0;
}

/*
std::vector<std::pair<int, int>> Rules::getPositions(Piece pcs, bool type)
{
    std::string aux_board[9][9][2];


    if (board[pos.first][pos.second][type] == "Pawn")
    {
    //saving the board, we are  going to simulate the move and see if valid
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            for (int k = 0; k < 2; k++)
                aux_board[i][j][k] = board[i][j][k];
    


    }
    

}
*/