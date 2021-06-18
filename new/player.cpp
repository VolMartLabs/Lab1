#include "player.h"

void printMove(Move m)
{
    std::cout << "Move: " << m.start.col << " " << m.start.row << " to " << m.end.col << " " << m.end.row << "\n";
}

void clear()
{
    system("CLS");
}

Player::Player(std::string n, Side s) {
    name = n;
    side = s;
}

Status Player::makeMove(Move move, Board board)
{
    return board.makeMove(move, side);
}

Side Player::getSide()
{
    return side;
}

Status AI::makeMove(Board board)
{
    Move move = minimaxStart(board, getSide(), true);
    std::cout << "AI made move: ";
    printMove(move);
    std::cout << "\n";
    Status move_status = board.makeMove(move, getSide());
    return move_status;
}

Move AI::minimaxStart(Board board, Side s, bool maximizing)
{
    int alpha = -1000, beta = 1000;
    std::vector<Move> possible_moves;
    board.genAllMoves(s, possible_moves);
    std::vector<double> heuristics;
    if (possible_moves.empty()) {
        std::cout << "NO POSSIBLE MOVES\n";
        return { -1 };
    }
    Board tempBoard;
    int num_moves = possible_moves.size();
    for (int i = 0; i < num_moves; i++) {
        tempBoard = *board.clone();
        Status status = tempBoard.makeMove(possible_moves[i], s);
        heuristics.push_back(minimax(tempBoard, switchSide(s), !maximizing, depth - 1, alpha, beta));
    }
    double max_heuristics = -1000;
    int num_heuristics = heuristics.size();
    for (int i = num_heuristics - 1; i >= 0; i--) {
        if (heuristics[i] >= max_heuristics) {
            max_heuristics = heuristics[i];
        }
    }
    for (int i = 0; i < num_heuristics; i++) {
        if (heuristics[i] < max_heuristics) {
            heuristics.erase(heuristics.begin() + i);
            possible_moves.erase(possible_moves.begin() + i);
            i--;
            num_heuristics--;
        }
    }
    num_moves = possible_moves.size();
    Move final_move = possible_moves[rand() % num_moves];
    return final_move;
}

double AI::minimax(Board board, Side s, bool maximizing, int depth, int alpha, int beta) {
    if (depth == 0) {
        return getHeuristic(board);
    }
    std::vector<Move> possible_moves;
    board.genAllMoves(s, possible_moves);
    int n = possible_moves.size();
    int initial = 0;
    Board tempBoard;
    if (maximizing) {
        for (int i = 0; i < n; i++) {
            tempBoard = *board.clone();
            Status status = tempBoard.makeMove(possible_moves[i], s);
            if (status != Status::COMPLETED && status != Status::GAME_OVER) {
                continue;
            }
            int result = minimax(tempBoard, switchSide(s), !maximizing, depth - 1, alpha, beta);
            initial = std::max(result, initial);
            alpha = std::max(initial, alpha);
            if (alpha >= beta) {
                break;
            }
        }
    }
    else {
        initial = 1000;
        for (int i = 0; i < n; i++) {
            tempBoard = *board.clone();
            Status status = tempBoard.makeMove(possible_moves[i], s);
            if (status != Status::COMPLETED && status != Status::GAME_OVER) {
                continue;
            }
            int result = minimax(tempBoard, switchSide(s), !maximizing, depth - 1, alpha, beta);
            initial = std::min(result, initial);
            beta = std::min(beta, initial);
            if (alpha >= beta) {
                break;
            }
        }
    }
    return initial;
}

double AI::getHeuristic(Board board) {
    double king_weight = 1.5;
    if (getSide() == Side::BLACK_SIDE) {
        return (king_weight * board.getNumBlackKings() + board.getNumBlack()) - (king_weight * board.getNumWhiteKings() + board.getNumWhite());
    }
    return (king_weight * board.getNumWhiteKings() + board.getNumWhite()) - (king_weight * board.getNumBlackKings() + board.getNumBlack());
}

Side AI::switchSide(Side side) {
    if (side == Side::BLACK_SIDE) {
        return Side::WHITE_SIDE;
    }
    return Side::BLACK_SIDE;
}