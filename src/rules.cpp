#include "../include/rules.h"
#include "../include/piece.h"

#include <string>
#include <vector>
#include <iostream>


Rules::~Rules()
{
    
}


std::vector <std::pair<int, int> > Rules::canAttackPos(std::pair<int, int> pos, int player)
{
        
    std::vector<std::pair<int, int> > ans;

    if(board[player][pos.first][pos.second] == nullptr) return ans;
    for (auto way : board[player][pos.first][pos.second]->path())
        for (auto p : way)
        {
            if (board[player][p.first][p.second] != nullptr)
                break;
            ans.push_back(std::make_pair(p.first, p.second));
            if (board[player][p.first][p.second] != nullptr)
                break;
        }        
    return ans;
}

bool Rules::isInCheck(int player)
{
    
    bool mat[9][9];
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[(player + 1) % 2][i][j]!=nullptr)
                {
                    pos = canAttackPos(std::make_pair(i,j), !player);
                    for (auto it:pos)
                        mat[it.first][it.second] = 1;
                    pos.clear();
                }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[player][i][j]->getType() == "King")
                return mat[i][j];
    return 0;
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

std::vector<std::pair<int, int>> Rules::getFuturePositions(Piece pcs){

    int player = pcs.getPlayer();
    std:: cout<<"\n";
    if(player!=current_player) return {};

    Piece* aux_board[2][8][8];
    std::pair<int, int> pos = pcs.getPos();
    std::vector<std::pair<int, int>> ans;
    std::vector<std::pair<int, int>> location;
    
    saveBoard(aux_board);
    if (board[player][pos.first][pos.second] == nullptr)
        return ans;
    
    //std:: cout << board[player][pos.first][pos.second]->getType();
    if (board[player][pos.first][pos.second]->getType() == "Pawn") {
        
        //return {{pos.first, pos.second-1}};

        //pawn can move back and front, but can only attack sideways, so we are gonna check
        //if we can move up and down first

        int dst = -1;
        //to keep track where we going
        if (player == 0) {
            dst = 1;
        }
        if (board[0][pos.first][pos.second + dst] != nullptr and board[1][pos.first][pos.second + dst] != nullptr) {
            std::cout << "lmao";
            board[player][pos.first][pos.second + dst]->getType() = "Pawn";
            board[!player][pos.first][pos.second + dst] = nullptr;
            board[player][pos.first][pos.second + dst] = nullptr;
            //if (!isInCheck(player))
                ans.push_back(std::make_pair(pos.first, pos.second + dst));
            getBoard(aux_board);
            if (!pcs.getHasMoved()) {
                dst *= 2;
                if (board[0][pos.first][pos.second + dst]!=nullptr and board[1][pos.first][pos.second + dst]!=nullptr) {
                    saveBoard(aux_board);
                    board[player][pos.first][pos.second + dst]->getType() = "Pawn";
                    board[!player][pos.first][pos.second + dst]->getType() = "";
                    board[player][pos.first][pos.second + dst]->getType() = "";
                    //if (!isInCheck(0))
                        ans.push_back(std::make_pair(pos.first, pos.second + dst));
                }
                getBoard(aux_board);
            }
        }
        /*
        location = this->canAttackPos(pos, player);
        for (auto it:location) {
            board[player][it.first][it.second] = board[player][pos.first][pos.second];
            board[!player][it.first][it.second]->getType() = "";
                board[player][pos.first][pos.second]->getType() = "";
            if (!isInCheck(player))
                ans.push_back(it);
            getBoard(aux_board);
        
        }
        */
    }
    return ans;
}
