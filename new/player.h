#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <time.h>

#include "board.h"
#include "enumlist.h"
#include "structs.h"

void clear();
void printMove(Move m);

class Player {
protected:
    Side side;
    std::string name;
public:
    Player(std::string n, Side s);
    Side getSide();
    virtual Status makeMove(Move move, Board b);
};

class AI : public Player {
private:
    int depth;
public:
    AI(std::string name, Side side) : Player(name, side) {
        depth = 3;
    };
    Status makeMove(Board board);
    Move minimaxStart(Board board, Side side, bool maximizing);
    double minimax(Board board, Side side, bool maximizing, int depth, int alpha, int beta);
    double getHeuristic(Board board);
    Side switchSide(Side side);
};
