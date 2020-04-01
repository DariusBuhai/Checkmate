#include "../include/rules.h"
#include "../include/piece.h"
#include <string>
#include <vector>

Rules::Rules(std::vector<Piece> items)
{
    pieces.clear();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j][0] = "", board[i][j][1] = "";

    for (auto it : items)
        board[it.getPos().first][it.getPos().second][it.getIsBlack()] =
        it.getType();
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
}