#include "../include/rules.h"
#include "../include/draw.h"
#include "../include/table.h"
#include "../include/types.h"
#include <string>
#include <vector>
#include <iostream>


Rules::~Rules(){}

std::vector<std::pair<int, int>> Rules::canAttackPos(Piece* pcs){
    std::vector<std::pair<int, int>> ans;
    for(auto l: pcs->path()){
        for (auto p : l){
            if (board[pcs->getPlayer()][p.first][p.second] != nullptr)
                break;
            ans.emplace_back(p);
            if (board[!pcs->getPlayer()][p.first][p.second] != nullptr)
                break;
        }
    }
    return ans;
}

bool Rules::isInCheck(int player){
    bool mat[9][9];
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[(player + 1) % 2][i][j]!=nullptr){
                    pos = canAttackPos(board[player][i][j]);
                    for (auto it:pos)
                        mat[it.first][it.second] = 1;
                    pos.clear();
                }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[player][i][j]->getType() == "King")
                return mat[i][j];
    return false;
}

inline void Rules::saveBoard(Piece* aux_board[2][8][8]){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                if(board[i][j][k]!= nullptr)
                    aux_board[i][j][k] = board[i][j][k];
}


inline void Rules::getBoard(Piece* aux_board[2][8][8]){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                board[i][j][k] = aux_board[i][j][k];
}

std::vector<std::pair<int, int>> Rules::getFuturePositions(Piece* pcs){

    int player = pcs->getPlayer();

    if(player!=current_player) return {};

    if(pcs->getType()!="Pawn" || 1==1)
        {
            return canAttackPos(pcs);
        }
    //std::cout<<"e pion"<<'\n';
    Piece* aux_board[2][8][8];
    std::vector<std::pair<int, int>> ans;
    std::pair<int, int> pos = pcs->getPos();

    saveBoard(aux_board);

    int dst = -1;
    if (player == 0) dst = 1;

    if (board[0][pos.first][pos.second + dst] != nullptr or board[1][pos.first][pos.second + dst] != nullptr) {
        std::cout << "lmao";
        board[player][pos.first][pos.second + dst]->getType() = "Pawn";
        board[!player][pos.first][pos.second + dst] = nullptr;
        board[player][pos.first][pos.second + dst] = nullptr;
        //if (!isInCheck(player))
        ans.emplace_back(std::make_pair(pos.first, pos.second + dst));
        getBoard(aux_board);
        if (!pcs->getHasMoved()) {
            dst *= 2;
            if (board[0][pos.first][pos.second + dst]!=nullptr and board[1][pos.first][pos.second + dst]!=nullptr) {
                saveBoard(aux_board);
                board[player][pos.first][pos.second + dst]->getType() = "Pawn";
                board[!player][pos.first][pos.second + dst]->getType() = "";
                board[player][pos.first][pos.second + dst]->getType() = "";
                //if (!isInCheck(0))
                ans.emplace_back(std::make_pair(pos.first, pos.second + dst));
            }
            getBoard(aux_board);
        }
    }

    /*for (auto it:this->canAttackPos(pcs)) {
        board[player][it.first][it.second] = pcs;
        board[!player][it.first][it.second]->getType() = "";
            pcs->getType() = "";
        if (!isInCheck(player))
            ans.push_back(it);
        getBoard(aux_board);

    }*/
    return ans;
}
