#include "board.h"

Board::Board() {
    setUpBoard();
}

Board::Board(PieceType** b) {
    numBlack = 0;
    numWhite = 0;
    numBlackKings = 0;
    numWhiteKings = 0;
    board = b;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            PieceType piece = getPiece(i, j);
            if (piece == BLACK || piece == BLACK_KING) {
                numBlack++;
                if (piece == BLACK_KING) {
                    numBlackKings++;
                }
            }
            else if (piece == WHITE || piece == WHITE_KING) {
                numWhite++;
                if (piece == WHITE_KING) {
                    numWhiteKings++;
                }
            }
        }
    }
}

PieceType Board::getPiece(int i, int j) {
    return board[i][j];
}

void Board::setUpBoard() {
    numBlack = 12;
    numWhite = 12;
    numBlackKings = 0;
    numWhiteKings = 0;
    board = new PieceType * [8];
    for (int i = 0; i < 8; i++) {
        board[i] = new PieceType[8];
    }
    for (int i = 0; i < 8; i++) {
        int first = 0;
        if (i % 2 == 0) {
            first = 1;
        }
        PieceType piece = EMPTY;
        if (i <= 2) {
            piece = WHITE;
        }
        else if (i >= 5) {
            piece = BLACK;
        }
        for (int j = first; j < 8; j += 2) {
            board[i][j] = piece;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!(board[i][j] == BLACK || board[i][j] == WHITE) || (i > 2 && i < 5)) {
                board[i][j] = EMPTY;
            }
        }
    }
}

int Board::getNumBlack() {
    return numBlack;
}

int Board::getNumWhite() {
    return numWhite;
}

int Board::getNumBlackKings() {
    return numBlackKings;
}

int Board::getNumWhiteKings() {
    return numWhiteKings;
}

void Board::genAllMoves(Side side, std::vector<Move>& moves) {
    PieceType normal = side == BLACK_SIDE ? BLACK : WHITE;
    PieceType king = side == BLACK_SIDE ? BLACK_KING : WHITE_KING;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            PieceType piece = getPiece(i, j);
            if (piece == normal || piece == king) {
                genValidJumpMoves(i, j, side, moves);
            }
        }
    }
    if (moves.empty()) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                PieceType piece = getPiece(i, j);
                if (piece == normal || piece == king) {
                    genValidMoves(i, j, side, moves);
                }
            }
        }
    }
}

void Board::genValidMoves(int r, int c, Side side, std::vector<Move>& moves) {
    PieceType piece = board[r][c];
    if (piece == EMPTY) 
    {
        std::cout << "EMPTY PIECE\n";
        throw Failure();
    }

    if (piece == WHITE || piece == BLACK) 
    {
        int rowChange = piece == BLACK ? -1 : 1;
        int newRow = r + rowChange;
        if (newRow >= 0 && newRow < 8) 
        {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) 
            {
                moves.push_back({ r, c, newRow, newCol });
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) 
            {
                moves.push_back({ r, c, newRow, newCol });
            }
        }
    }
    else {
        int newRow = r + 1;
        if (newRow < 8) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) 
            {
                moves.push_back({ r, c, newRow, newCol });
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) 
            {
                moves.push_back({ r, c, newRow, newCol });
            }
        }
        newRow = r - 1;
        if (newRow >= 0) {
            int newCol = c + 1;
            if (newCol < 8 && getPiece(newRow, newCol) == EMPTY) 
            {
                moves.push_back({ r, c, newRow, newCol });
            }
            newCol = c - 1;
            if (newCol >= 0 && getPiece(newRow, newCol) == EMPTY) 
            {
                moves.push_back({ r, c, newRow, newCol });
            }
        }
    }
}

void Board::genValidJumpMoves(int r, int c, Side side, std::vector<Move>& moves) {
    Point start = { r, c };
    std::vector<Point> possible_moves;
    if (side == WHITE_SIDE && getPiece(r, c) == WHITE) 
    {
        possible_moves.push_back({ r + 2, c + 2 });
        possible_moves.push_back({ r + 2, c - 2 });
    }
    else if (side == BLACK_SIDE && getPiece(r, c) == BLACK) 
    {
        possible_moves.push_back({ r - 2, c + 2 });
        possible_moves.push_back({ r - 2, c - 2 });
    }
    else if (getPiece(r, c) == BLACK_KING || getPiece(r, c) == WHITE_KING) 
    {
        possible_moves.push_back({ r + 2, c + 2 });
        possible_moves.push_back({ r + 2, c - 2 });
        possible_moves.push_back({ r - 2, c + 2 });
        possible_moves.push_back({ r - 2, c - 2 });
    }
    int n = possible_moves.size();
    for (int i = 0; i < n; i++) 
    {
        Point temp = possible_moves[i];
        Move m = { start, temp };
        Point mid = getMidSquare(m);
        if (temp.row >= 0 && temp.row < 8 && temp.col >= 0 && temp.col < 8 && getPiece(temp.row, temp.col) == EMPTY && isOpponentPiece(side, getPiece(mid))) 
        {
            moves.push_back(m);
        }
    }
}

PieceType Board::getPiece(Point p) 
{
    return board[p.row][p.col];
}

Point Board::getMidSquare(Move m) 
{
    Point middle = { (m.start.row + m.end.row) / 2, (m.start.col + m.end.col) / 2 };
    return middle;
}

bool Board::isOpponentPiece(Side side, PieceType piece) 
{
    if (side == BLACK_SIDE) 
    {
        return piece == WHITE || piece == WHITE_KING;
    }
    return piece == BLACK || piece == BLACK_KING;
}

bool Board::isOwnPiece(int r, int c, Side side) 
{
    PieceType piece = getPiece(r, c);
    if (side == BLACK_SIDE) 
    {
        return piece == BLACK || piece == BLACK_KING;
    }
    return piece == WHITE || piece == WHITE_KING;
}

Status Board::makeMove(Move move, Side side) 
{
    // TODO: CHECK FOR GAME OVER
    if (move.start.row == -1) 
    {
        return GAME_OVER;
    }
    Point start = move.start;
    int startRow = start.row;
    int startCol = start.col;
    Point end = move.end;
    int endRow = end.row;
    int endCol = end.col;
    PieceType current_piece = getPiece(startRow, startCol);
    if (!isOwnPiece(startRow, startCol, side) || getPiece(startRow, startCol) == EMPTY) 
    {
        return FAILED_INVALID_PIECE;
    }
    std::vector<Move> possible_moves;
    genAllMoves(side, possible_moves);
    bool move_in_list = false;
    int n = possible_moves.size();
    for (int i = 0; i < n && !move_in_list; i++) {
        move_in_list = movesEqual(possible_moves[i], move);
    }
    if (move_in_list) 
    {
        bool jump = false;
        if (startRow + 1 == endRow || startRow - 1 == endRow) 
        {
            board[startRow][startCol] = EMPTY;
            board[endRow][endCol] = current_piece;
        }
        else 
        {
            jump = true;
            board[startRow][startCol] = EMPTY;
            board[endRow][endCol] = current_piece;
            Point middle_square = getMidSquare(move);
            PieceType middle_piece = getPiece(middle_square);
            if (middle_piece == BLACK) 
            {
                numBlack--;
            }
            else if (middle_piece == WHITE) 
            {
                numWhite--;
            }
            else if (middle_piece == BLACK_KING) 
            {
                numBlack--;
                numBlackKings--;
            }
            else if (middle_piece == WHITE_KING) 
            {
                numWhite--;
                numWhiteKings--;
            }
            board[middle_square.row][middle_square.col] = EMPTY;
        }
        if (endRow == 0 && side == BLACK_SIDE) 
        {
            board[endRow][endCol] = BLACK_KING;
            numBlackKings++;
        }
        else if (endRow == 7 && side == WHITE_SIDE) 
        {
            board[endRow][endCol] = WHITE_KING;
            numWhiteKings++;
        }
        return COMPLETED;
    }
    else 
    {
        return FAILED_INVALID_DEST;
    }
}

bool Board::movesEqual(Move one, Move two) 
{
    return one.start.row == two.start.row && one.start.col == two.start.col && one.end.row == two.end.row && one.end.col == two.end.col;
}

Board* Board::clone() {
    PieceType** new_board = new PieceType * [8];
    for (int i = 0; i < 8; i++) {
        new_board[i] = new PieceType[8];
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            new_board[i][j] = board[i][j];
        }
    }
    Board* b = new Board(new_board);
    return b;
}

void Board::drawBoard()
{
    std::cout << "    ";
    for (int i = 0; i < 8; i++) {
        std::cout << "0" << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i <= 16; i++) {
        if (i % 2 == 0) {
            std::cout << "    ";
            for (int j = 0; j < 23; j++) {
                std::cout << "-";
            }
            std::cout << " ";
        }
        else {
            std::cout << "0" << i / 2 << " ";
            for (int j = 0; j < 8; j++) {
                std::cout << "|";
                PieceType p = board[i / 2][j];
                if (p == BLACK) 
                {
                    std::cout << "BP";
                }
                else if (p == BLACK_KING) 
                {
                    std::cout << "BK";
                }
                else if (p == WHITE) 
                {
                    std::cout << "WP";
                }
                else if (p == WHITE_KING) 
                {
                    std::cout << "WK";
                }
                else if (p == EMPTY) 
                {
                    std::cout << "  ";
                }
            }
            std::cout << "| 0" << i / 2;
        }
        std::cout << "\n";
    }
    std::cout << "    ";
    for (int i = 0; i < 8; i++) {
        std::cout << "0" << i << " ";
    }
    std::cout << "\n\nBP = Black Piece / BK = Black King / WP = White Piece / WK = White King\n\n\n";
}