/**
\file
\brief .h file of player and AI classes

contains player functions and AI implementation
*/

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <time.h>

#include "board.h"
#include "enumlist.h"
#include "structs.h"

/**
\brief function that clears the console
*/
void clear();

/**
\brief function that prints player's move
*/
void printMove(Move m);


/**
\brief player class that contains player side and move possibility
*/
class Player {
protected:
    Side side; // shows which side player choosed
    std::string name; // player's name
public:
    /**
    \brief Player setter

    \param n name of the player
    \param s side of the player
    */
    Player(std::string n, Side s);

    /**
    \brief gets the side of the player
    */
    Side getSide();
    /**
    \brief moves a piece

    \param n particular move
    \param s board in which operation takes place
    */
    virtual Status makeMove(Move move, Board b);
};

/**
\brief AI class that contains minmax algorithm
*/
class AI : public Player {
private:
    int depth; // depth for depth-first search algorithm for the exploration of the complete game tree
public:
    AI(std::string name, Side side) : Player(name, side) {
        depth = 3;
    };
    /**
    \brief moves a piece

    \param board board in which operation takes place
    */
    Status makeMove(Board board);

    /**
    \brief starts minimax algorithm

    \param board board in which operation takes place
    \param side side of the AI
    \param maximizing tells if this is min or max
    */
    Move minimaxStart(Board board, Side side, bool maximizing);

    /**
    \brief moves a piece

    \param board board in which operation takes place
    \param side side of the AI
    \param maximizing tells if this is min or max
    \param depth for depth-first search algorithm for the exploration of the complete game tree
    \param alpha estimation for the node: if node value bigger then any alpha value it initializes this value to alpha
    \param beta estimation for the node: if node value smaller then any another node value it initializes this value to beta
    */
    double minimax(Board board, Side side, bool maximizing, int depth, int alpha, int beta);

    /**
    \brief gets heuristic value of the node

    \param board board in which operation takes place
    */
    double getHeuristic(Board board);

    /**
    \brief switches side of the AI

    \param side takes current side for AI and switches it to another one
    */
    Side switchSide(Side side);
};
