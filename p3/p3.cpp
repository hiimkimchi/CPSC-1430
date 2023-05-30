// Bryan Kim
// p3.cpp
// This file takes Tic Tac Toe and modifies it. The user can choose the size of the
// board in the beginning and this .cpp file implements Board and Player classes.

#include "board.h"
#include "player.h"
#include <iostream>

int const  LINE_CLEAR = 50;
char const QUIT       = 'y';

// desc: Prints 50 new lines to "clear" the terminal
// pre : none
// post: none
void clear_screen();

// desc: Runs through the game. Keeps score and asks players if they want to play again.
// pre : must have player.h and board.h included
// post: none
int main() {
    int    size;
    int    x   = 0;
    int    y   = 0;
    char   yes = 'y';
    char   current_char;
    bool   is_full;
    bool   is_won;
    bool   is_player1_turn = true;
    bool   space_taken     = false;
    Player player_1;
    Player player_2;
    Player current_player;
    player_1.set_symbol('O');
    player_2.set_symbol('X');

    // welcome remarks
    std::cout << "Welcome to Tic Tac Toe.\nTwo players will play this game:\n"
              << "Player 1 (O) and Player 2 (X).\n\n\n";
    while (tolower(yes) == QUIT) {
        is_full        = false;
        is_won         = false;
        current_player = player_1;
        // ask users for size (error check for bad size)
        std::cout << "Please enter the desired size of your board: ";
        std::cin >> size;
        while (size < 0) {
            std::cout << "Please enter a size that is greater than 0: ";
            std::cin >> size;
        }

        Board board(size);
        while (!is_full && !is_won) {
            if (is_player1_turn) {
                current_player  = player_1;
                current_char    = player_1.get_symbol();
                is_player1_turn = false;
            } else {
                current_player  = player_2;
                current_char    = player_2.get_symbol();
                is_player1_turn = true;
            }

            clear_screen();
            board.display();
            if (space_taken) {
                std::cout << "\nSpace is already taken.\n";
            }

            std::cout << "\n"
                      << current_char << ", please provide a coordinate "
                      << "(input as \"x y\"): ";
            std::cin >> x >> y;
            space_taken = board.set_element(x, y, current_char);
            // update is_Full and is_Won
            is_full = board.is_full();
            is_won  = board.is_winner(current_player);
        }
        board.display();
        if (is_full) {
            std::cout << "\nThe board is full.";
        } else if (board.is_winner(player_1)) {
            std::cout << "\nPlayer 1 (O's) won the game.";
            player_1.award_point();
        } else {
            std::cout << "\nPlayer 2 (X's) won the game.";
            player_2.award_point();
        }
        std::cout << "\n\n\nPlayer 1 has " << player_1.get_points() << " points."
                  << "\nPlayer 2 has " << player_2.get_points() << " points."
                  << "\n\nWould you like to play again?: ";
        std::cin >> yes;
    }
    std::cout << "\n\nThank you for playing.\n\n\n";
    return 0;
}

void clear_screen() {
    for (int i = 0; i < LINE_CLEAR; i++) {
        std::cout << std::endl;
    }
}