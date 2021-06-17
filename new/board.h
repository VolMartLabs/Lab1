/**
\file
\brief .h file of Board class implementation
*/

#pragma once
#include <vector>
#include <iostream>

#include "enumlist.h"
#include "structs.h"

class Failure {};

/**
\brief Board class implementation
*/
class Board {
private:
    PieceType** board; // double pointer to particular place on the board (since our board is basically two-dimensional array)
    int numBlack; // number of black pieces on the board
    int numWhite; // number of white pieces on the board
    int numBlackKings; // number of black kings pieces on the board
    int numWhiteKings; // number of white kings pieces on the board
public:
    Board();
    /**
    \brief counts how many(and which) pieces are in the board

    \param b board in which operation takes place
    */
    Board(PieceType** b);

    /**
    \brief checks if particular piece is piece of the opponent

    \param b board in which operation takes place
    \param side side by which function is called
    */
    bool isOpponentPiece(Side side, PieceType piece);

    /**
    \brief checks if particular piece is your own

    \param r x coordinate of board
    \param c y coordinate of board
    \param side side by which function is called
    */
    bool isOwnPiece(int r, int c, Side side);

    /**
    \brief checks if moves are equal

    \param one first move
    \param two second move
    */
    bool movesEqual(Move one, Move two);

    /**
    \brief gets number of black pieces
    */
    int getNumBlack();

    /**
    \brief gets number of white pieces
    */
    int getNumWhite();

    /**
    \brief gets number of black king pieces
    */
    int getNumBlackKings();

    /**
    \brief gets number of white king pieces
    */
    int getNumWhiteKings();

    /**
    \brief clones the board
    */
    Board* clone();

    /**
    \brief gets the piece on coordinates (x; y)

    \param i x coordinate of board
    \param j y coordinate of board
    */
    PieceType getPiece(int i, int j);
    /**
    \brief gets the piece on Point(x; y)

    \param p Point on the board
    */
    PieceType getPiece(Point p);

    /**
    \brief divides coordinates of the move points by 2 (x/2, y/2) and returns a point with coorninates inbetween start and end position 

    \param move particular move we need
    */
    Point getMidSquare(Move move);

    /**
    \brief makes move from point start to point end

    \param move particular move we need
    \param side side by which function is called
    */
    Status makeMove(Move move, Side side);

    /**
    \brief draws the board
    */
    void drawBoard();

    /**
    \brief generates all moves pieces can take

    \param side side by which function is called
    \param moves vector which contains generated moves
    */
    void genAllMoves(Side side, std::vector<Move>& moves);

    /**
    \brief generates new valid jump moves for beating another piece

    \param r x coordinate of start point
    \param c y coordinate of start point
    \param side side by which function is called
    \param moves vector which contains generated jumpmoves
    */
    void genValidJumpMoves(int r, int c, Side side, std::vector<Move>& moves);

    /**
    \brief generates new valid moves on the board

    \param r x coordinate of start point
    \param c y coordinate of start point
    \param side side by which function is called
    \param moves vector which contains generated jumpmoves
    */
    void genValidMoves(int r, int c, Side side, std::vector<Move>& moves);

    /**
    \brief sets up the board and initializes constants
    */
    void setUpBoard();
};
