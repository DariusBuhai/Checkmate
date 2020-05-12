#ifndef CHECKMATE_BRAIN_H
#define CHECKMATE_BRAIN_H

#include <map>

#include "rules.h"
#include "piece.h"

class Brain : public Rules{
private:
    Rules* rules;
    int player = 1;
    int moves = 0;
    std::map<std::string, std::vector<std::vector<int>> >  evaluation;
    std::vector<std::vector<std::vector<Piece*>> >  boardBrain;
    static int getPointsEvaluation(Piece*);
    int getEvaluation(Piece*, std::pair<int,int>);
    std::vector<Move>last_AI_moves;
public:
    Brain(Rules*);
    Evaluation evalAttacked(Piece*,std::pair<int,int>);
    Evaluation evalProtected(Piece*,std::pair<int,int>);
    bool isOkToMove(Piece*,std::pair<int,int>);
    bool canCheck(Piece*,std::pair<int,int>);
    bool pieceIsAttacked(Piece*,std::pair<int,int>);
    Move determineBestMove();
    int getMoves();
    void initializeEvaluation();
    inline void copyBoard();
    bool checkLast3Moves(Move);
    Move determineBestStockfishMove();
    friend std::ostream& operator<<(std::ostream& , const Brain&);
    ~Brain();
};

#endif //CHECKMATE_BRAIN_H
