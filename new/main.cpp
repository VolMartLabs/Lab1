#include "player.h"
#include "board.h"

void playGame() 
{
    char p, dummy;
    Side player, cpu;
    do 
    {
        std::cout << "Pick a side (b or w) ";
        std::cin >> p;
    } while (!(p == 'b' || p == 'w'));
    clear();
    if (p == 'b') 
    {
        player = BLACK_SIDE;
        cpu = WHITE_SIDE;
    }
    else if (p == 'w') 
    {
        player = WHITE_SIDE;
        cpu = BLACK_SIDE;
    }
    Player one("Player", player);
    AI two("CPU", cpu);
    bool player_turn = true;
    Board board;
    Status msg = COMPLETED;
    while (msg != GAME_OVER) 
    {
        clear();
        std::cout << "\n\n";
        if (player_turn) 
        {
            std::cout << "------------Player Move------------\n";
        }
        else 
        {
            std::cout << "-------------CPU Move--------------\n";
        }
        std::cout << "\n\n";
        board.drawBoard();
        if (!player_turn) 
        {
            system("pause");
        }
        if (player_turn) 
        {
            std::vector<Move> player_moves;
            board.genAllMoves(one.getSide(), player_moves);
            if (player_moves.empty()) 
            {
                std::cout << "No possible player moves, you lose\n";
                break;
            }
            else 
            {
                int num_moves = player_moves.size();
                std::cout << "Possible moves (must make jump moves when possible):\n";
                for (int i = 0; i < num_moves; i++) 
                {
                    printMove(player_moves[i]);
                }
                std::cout << "\n\n";
            }
            Move move;
            do {
                std::cout << "Enter your move (four space-separated integers x1 y1 x2 y2): ";
                std::cin >> move.start.col >> move.start.row >> move.end.col >> move.end.row;
                msg = one.makeMove(move, board);
                if (msg == FAILED_INVALID_DEST) {
                    std::cout << "Invalid move\n";
                }
                else if (msg == FAILED_INVALID_PIECE) {
                    std::cout << "Invalid chosen piece\n";
                }
            } while (msg != COMPLETED && msg != GAME_OVER);
            player_turn = !player_turn;
        }
        else 
        {
            std::vector<Move> ai_moves;
            board.genAllMoves(two.getSide(), ai_moves);
            if (ai_moves.empty()) {
                std::cout << "No possible cpu moves, you win\n";
            }
            msg = two.makeMove(board);
            player_turn = !player_turn;
        }
    }
}

int main() {
    srand(time(NULL));
    clear();
    std::cout << "\n\n\n-------------- Welcome to AI Checkers --------------\n";
    char play_again;
    do {
        playGame();
        do {
            std::cout << "Would you like to play again? (y/n) ";
            std::cin >> play_again;
        } while (!(play_again == 'y' || play_again == 'n'));
    } while (play_again == 'y');
    return 0;
}