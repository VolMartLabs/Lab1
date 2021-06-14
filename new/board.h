#pragma once
#include <vector>
#include <iostream>

#include "enumlist.h"
#include "structs.h"

class Failure {};

class Board {
private:
    PieceType** board;
    int numBlack;
    int numWhite;
    int numBlackKings;
    int numWhiteKings;
public:
    Board();
    Board(PieceType** b);
    bool isOpponentPiece(Side side, PieceType);
    bool isOwnPiece(int r, int c, Side side);
    bool movesEqual(Move one, Move two);
    int getNumBlack();
    int getNumWhite();
    int getNumBlackKings();
    int getNumWhiteKings();
    Board* clone();
    PieceType getPiece(int i, int j);
    PieceType getPiece(Point p);
    Point getMidSquare(Move move);
    Status makeMove(Move move, Side side);
    void drawBoard();
    void genAllMoves(Side side, std::vector<Move>& moves);
    void genValidJumpMoves(int r, int c, Side side, std::vector<Move>& moves);
    void genValidMoves(int r, int c, Side side, std::vector<Move>& moves);
    void setUpBoard();
};
