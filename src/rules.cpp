#include "../include/rules.h"
#include "../include/table.h"
#include "../include/types.h"

#include <string>
#include <vector>
#include <iostream>

Rules::Rules(){
    Pieces();
}

Rules::~Rules() = default;





std::vector<std::pair<int, int>> Rules::canAttackPos(Piece* pcs)
{
    //returns where a position can move without considering check.
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

bool Rules::isInCheck(int player)
{
    //checks if the current player is in check
    //also, check if the opponent king piece is not capturated by mistake
    bool mat[9][9];
    bool haveKing = 0;
    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[!player][i][j] != nullptr)
            {
                if (dynamic_cast<King*>(board[!player][i][j]))
                    haveKing = 1;
                pos = canAttackPos(board[!player][i][j]);
                for (auto it:pos)
                    mat[it.first][it.second] = 1;
                pos.clear();
            }
    if (haveKing == 0)
        return 1;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[player][i][j] != nullptr)
                if (dynamic_cast<King*>(board[player][i][j]))
                    return mat[i][j];
    return false;
}

inline void Rules::saveBoard(Piece* aux_board[2][8][8])
{
    //save the curent state of the board.
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                aux_board[i][j][k] = board[i][j][k];
}


inline void Rules::getBoard(Piece* aux_board[2][8][8])
{
    //gets the board back to the original state.
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 8; k++)
                board[i][j][k] = aux_board[i][j][k];
}

std::vector<std::pair<int, int>> Rules::getFuturePawn(Piece* pcs)
{
    Piece* aux_board[2][8][8];
    saveBoard(aux_board);

    int player = pcs->getPlayer();
    std::vector<std::pair<int, int>> ans;
    std::pair<int, int> pos = pcs->getPos();
    //if we go up or down
    int dst = -1;
    if (player == 1)
        dst = 1;
    if((pos.first >= 0 and pos.first <=7) and (pos.second + dst <=7 and pos.second + dst >= 0))
        if (board[0][pos.first][pos.second + dst] == nullptr or board[1][pos.first][pos.second + dst] == nullptr)
        {

            //make a virtual move of the piece and check if valid
            if( board[player][pos.first][pos.second + dst] == nullptr && board[!player][pos.first][pos.second + dst] == nullptr)
            {
                //std::cout<<"e pion"<<'\n';
                board[player][pos.first][pos.second + dst] = board[player][pos.first][pos.second];
                board[player][pos.first][pos.second] = nullptr;
                if (!isInCheck(player))
                    ans.emplace_back(std::make_pair(pos.first, pos.second + dst));
            }
            getBoard(aux_board);
            if(player!=currentPlayer)
                return {};
            //std::cout<<"e pion"<<'\n';
            //if it has never moved, it can move by 2 positions.
            if (!(pcs->getHasMoved()))
            {
                dst *= 2;
                if((pos.first >= 0 and pos.first <=7) and (pos.second + dst <=7 and pos.second + dst >= 0))
                    if (board[0][pos.first][pos.second + dst] == nullptr and board[1][pos.first][pos.second + dst] == nullptr)
                    {
                        board[player][pos.first][pos.second + dst] = board[player][pos.first][pos.second];
                        board[player][pos.first][pos.second] = nullptr;
                        if (!isInCheck(player))
                            ans.emplace_back(std::make_pair(pos.first, pos.second + dst));
                        getBoard(aux_board);
                    }
            }
            //check if it can attack on the sideways.
            dst = -1;
            if (player == 1)
                dst = 1;
            int posx,posy;
            posx = pos.first + 1;
            posy = pos.second + dst;
            if ((posx > -1 and posx < 8) and (posy > -1 and posy < 8))
                if (board[!player][posx][posy] != nullptr)
                {
                    board[!player][posx][posy] = nullptr;
                    board[player][posx][posy] = board[player][pos.first][pos.second];
                    board[player][pos.first][pos.second] = nullptr;
                    if (!isInCheck(player))
                        ans.push_back(std::make_pair(posx, posy));
                    getBoard(aux_board);
                }
            posx = pos.first - 1;
            posy = pos.second + dst;
            if ((posx > -1 and posx < 8) and (posy > -1 and posy < 8))
                if (board[!player][posx][posy] != nullptr)
                {
                    board[!player][posx][posy] = nullptr;
                    board[player][posx][posy] = board[player][pos.first][pos.second];
                    board[player][pos.first][pos.second] = nullptr;
                    if (!isInCheck(player))
                        ans.push_back(std::make_pair(posx, posy));
                    getBoard(aux_board);
                }
        }
    return ans;
}





void Rules::getAttackedPositions(bool mat[8][8], int player)
{

    std::vector<std::pair<int, int>> pos;
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
            mat[i][j] = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[!player][i][j] != nullptr)
            {
                pos = canAttackPos(board[!player][i][j]);
                for (auto it:pos)
                    mat[it.first][it.second] = 1;
                pos.clear();
            }
}


std::vector<std::pair<int, int>> Rules::canCastle(Piece* pcs)
{
    if (!(dynamic_cast<King*> (pcs)))
        return {};
    int player = pcs->getPlayer();
    if (!(pcs->getHasMoved()) and !(isInCheck(player)))
    {       
        bool isAttacked[8][8];
        // the king has to pass throught not attacked positions;
        getAttackedPositions(isAttacked, pcs->getPlayer());
        std::pair<int, int> pos = pcs->getPos();
        std::vector<std::pair<int, int>> ans;
        //bool canMove = true;
        //first we go to the right
        while (pos.first < 7)
        {
            pos.first ++ ;
            if (board[!player][pos.first][pos.second] != nullptr)
                break;
            if (isAttacked[pos.first][pos.second])
                break;
            if (board[player][pos.first][pos.second] != nullptr)
            {
                if (dynamic_cast<Rook*> (board[player][pos.first][pos.second]))
                {
                    if (!(board[player][pos.first][pos.second]->getHasMoved()))
                        ans.push_back(pos);
                }
                break;
            }
        }
        pos = pcs->getPos();
        while (pos.first > 1)
        {
            pos.first --;
            if (board[!player][pos.first][pos.second] != nullptr)
                break;
            if (isAttacked[pos.first][pos.second])
                break;
            if (board[player][pos.first][pos.second] != nullptr)
            {
                if (dynamic_cast<Rook*> (board[player][pos.first][pos.second]))
                {
                    if (!(board[player][pos.first][pos.second]->getHasMoved()))
                        ans.push_back(pos);
                }
                break;
            }
        }
        return ans;

    }
    return {};


}


std::vector<std::pair<int, int>> Rules::getFuturePositions(Piece* pcs){
    //returns the position that a piece can move.
    int player = pcs->getPlayer();

    if(player!=currentPlayer)
        return {};
    //to save the board

    Piece* aux_board[2][8][8];
    saveBoard(aux_board);
    std::vector<std::pair<int, int>> ans;
    std::vector<std::pair<int, int>> attack_pos;
    std::pair<int, int> pos = pcs->getPos();


    saveBoard(aux_board);


    if (dynamic_cast<Pawn*>(board[player][pos.first][pos.second])){
        return getFuturePawn(pcs);
    }
    else{
        if (dynamic_cast<King*>(board[player][pos.first][pos.second]))
            ans = canCastle(board[player][pos.first][pos.second]);

        attack_pos = canAttackPos(pcs);
        for (auto& next_pos : attack_pos)
        {
            board[player][next_pos.first][next_pos.second] =
                board[player][pos.first][pos.second];
            board[!player][next_pos.first][next_pos.second] = nullptr;
            board[player][pos.first][pos.second] = nullptr;
            if(!isInCheck(player))
                ans.push_back(next_pos);
            getBoard(aux_board);
        }
    }
    return ans;
}

bool Rules::isCheckMate(int player)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0 ; j < 8; j++)
        {
            if (board[player][i][j] != nullptr)
            {
                if ( (getFuturePositions(board[player][i][j])).size() != 0)
                {
                    return true;
                }
            }
        }
    return false;
}