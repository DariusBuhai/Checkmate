#include "../include/rules.h"
#include "../include/piece.h"
#include <string>
#include <vector>
#include <iostream>

std::vector <std::pair<int, int> > Rules::canAttackPos(std::pair<int, int> pos, int type)
{
    std::vector<std::pair<int, int> > ans;
    if(board[type][pos.first][pos.second] == nullptr) return ans;
    for (auto way : board[type][pos.first][pos.second]->path())
        for (auto p : way){
            if (board[type][p.first][p.second] == nullptr)
                break;
            ans.push_back(std::make_pair(p.first, p.second));
            if (board[type][p.first][p.second] == nullptr)
                break;
        }
    return ans;
}

bool Rules::isInCheck(int type)
{
    bool mat[9][9];
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[!type][i][j]!=nullptr)
                {
                    pos = canAttackPos(std::make_pair(i,j), !type);
                    for (auto it:pos)
                        mat[it.first][it.second] = 1;
                    pos.clear();
                }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[type][i][j]->getType() == "King")
                return mat[i][j];
    return 0;
}

inline void Rules::save_board(Piece aux_board[2][8][8]){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                if(board[i][j][k]!= nullptr)
                    aux_board[i][j][k] = *board[i][j][k];
}


inline void Rules::get_board(Piece aux_board[2][8][8]){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                board[i][j][k] = &aux_board[i][j][k];
}

std::vector<std::pair<int, int>> Rules::getPositions(Piece pcs, int type){
    Piece aux_board[2][8][8];
    std::pair<int, int> pos = pcs.getPos();
    std::vector<std::pair<int, int>> ans;
    std::vector<std::pair<int, int>> location;

    save_board(aux_board);
    if (board[type][pos.first][pos.second]->getType() == "Pawn") {

        return {{pos.first, pos.second-1}};

        //pawn can move back and front, but can only attack sideways, so we are gonna check
        //if we can move up and down first

        int dst = 1;
        //to keep track where we going
        if (type == 0) {
            dst = -1;
        }
        if (board[0][pos.first][pos.second + dst] != nullptr and board[1][pos.first][pos.second + dst] != nullptr) {
            board[type][pos.first][pos.second + dst]->getType() = "Pawn";
            board[!type][pos.first][pos.second + dst] = nullptr;
            board[type][pos.first][pos.second + dst] = nullptr;
            if (!isInCheck(type))
                ans.push_back(std::make_pair(pos.first, pos.second + dst));
            get_board(aux_board);
            if (!pcs.getHasMoved()) {
                dst *= 2;
                if (board[0][pos.first][pos.second + dst]!=nullptr and board[1][pos.first][pos.second + dst]!=nullptr) {
                    save_board(aux_board);
                    board[type][pos.first][pos.second + dst]->getType() = "Pawn";
                    board[!type][pos.first][pos.second + dst]->getType() = "";
                    board[type][pos.first][pos.second + dst]->getType() = "";
                    if (!isInCheck(0))
                        ans.push_back(std::make_pair(pos.first, pos.second + dst));
                }
                get_board(aux_board);
            }
        }
        location = this->canAttackPos(pos, type);
        for (auto it:location) {
            board[type][it.first][it.second] = board[type][pos.first][pos.second];
            board[!type][it.first][it.second]->getType() = "";
            board[type][pos.first][pos.second]->getType() = "";
            if (!isInCheck(type))
                ans.push_back(it);
            get_board(aux_board);
        }
    }
    return {};
}
