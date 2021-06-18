/**
\file
\brief .h file of enums used in program

contains enums PieceType, Side and Status
*/

#pragma once

/**Enum contains board tile status*/
enum class PieceType
{	
	/**Empty tile*/
    EMPTY, 
	/**Black piece*/
    BLACK, 
	/**White piece*/
    WHITE, 
	/**Black King piece*/
    BLACK_KING, 
	/**White King piece*/
    WHITE_KING 
};

/**Enum contains which side interacts*/
enum class Side
{
	/**Black side turn*/
    BLACK_SIDE,
	/**White side turn*/
    WHITE_SIDE
};

/**Enum contains status of the game*/
enum class Status
{
	/**Game is over*/
    COMPLETED,
	/**Player choosed invalid piece(empty)*/
    FAILED_INVALID_PIECE,
	/**Piece can't go to the destination player choosed*/
    FAILED_INVALID_DEST,
	/**Game is over #2*/
    GAME_OVER
};
