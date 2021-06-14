#pragma once

enum PieceType
{
    EMPTY,
    BLACK,
    WHITE,
    BLACK_KING,
    WHITE_KING
};

enum Side
{
    BLACK_SIDE,
    WHITE_SIDE
};

enum Status
{
    COMPLETED,
    FAILED_INVALID_PIECE,
    FAILED_INVALID_DEST,
    GAME_OVER
};
