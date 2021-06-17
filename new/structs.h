/**
\file
\brief .h file of Point and Move structures

contains Point and Move structs
*/

#pragma once

/**
\brief Point struct that contains row and coloumn of the piece
*/
struct Point 
{
    int row; // row of the piece
    int col; // coloumn of the piece
};

/**
\brief Move struct that contains starting point from piece's starting and moves it to end point
*/
struct Move 
{
    Point start; // start point where piece is
    Point end; // end point where piece should be
};
