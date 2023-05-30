// Bryan Kim
// p1.cpp
// This file simulates the game "Tic Tac Toe." Two players will try to get three of 
// their respective icons (O or X) in a row to win. Once a player wins, win count is
// kept and players are offered the option to replay.

#include <iostream>

int const MAX_X_INDEX= 3;
int const MAX_Y_INDEX = 3;
int const LINES = 11;
int const NUM_SPACES = 50;
char const SPACE = ' ';
char const YES = 'y';

//desc: Prints a welcome message for the users. Provides instructions on
//      on how to play and win conditions.
//pre : none
//post: none
void welcome();

//desc: Prints 50 new lines to help with game flow 
//pre : none
//post: none
void print_spaces();

//desc: Prints the 3x3 grid 
//pre : char 2D array must be [3][3].
//post: none
void print_grid(char icons[][MAX_Y_INDEX]);

//desc: Prints a reminder message to players on how to pick their desired space
//      in the grid.
//pre : none
//post: none
void print_reminder();

//desc: Takes turn, checks for user error and switches turns at the end of the call
//pre : char 2D array must be [3][3]
//      bool true = O's, bool false = X's
//      bool "turn" must be initialized in main
//post: bool "turn" will change everytime the function is called
void take_turn(char icons[][MAX_Y_INDEX], bool &turn);

//desc: Checks if there is 3 of the same icon in a row (diagonal, row, or column)
//pre : char 2D array must be [3][3]
//      int "winner" must be initialized in main
//post: int "winner" will be only 0, 1, or -1 if the return value is false.
bool check_win_cond(char icons[][MAX_Y_INDEX], int &winner);

//desc: Prints the result of the game and asks the player if they want to replay
//pre : int "o_counter" and "x_counter" must be initialized in main
//post: if returned "true" the game will restart
bool check_to_replay(int winner, int &o_counter, int &x_counter);

//desc: Clears the grid by putting a ' ' in each index
//pre : char 2D array must be [3][3]
//post: none
void clear_grid (char icons[][MAX_Y_INDEX]);

//desc: Runs through the Tic Tac Toe game. At the end of each game the user is
//      prompted to restart or end the game
//pre : consts must be declared and helper functions must be functional
//post: none
int main() {
    char icons[MAX_X_INDEX][MAX_Y_INDEX] = {{' ', ' ', ' '},{' ', ' ', ' '},
                                            {' ', ' ', ' '}};
    int winner = -1;
    int x_wins = 0;
    int o_wins = 0;
    bool is_first_player_turn = true;
    bool is_replaying = true;
    bool is_turns_continuing = true;

    //welcome message
    welcome();
    while (is_replaying) {
        while (is_turns_continuing) {
            //repeat: print grid, claim element, switch player
            print_spaces();
            print_reminder();
            print_grid(icons);
            take_turn(icons, is_first_player_turn);
            is_turns_continuing = check_win_cond(icons, winner);
        }
        //check if the user wants to replay, print results, and reset the game
        print_spaces();
        print_reminder();
        print_grid(icons);
        clear_grid(icons);
        is_replaying = check_to_replay(winner, o_wins, x_wins);
        is_turns_continuing = true;
    }
    std::cout << std::endl << "Thanks for playing, goodbye!" 
              << std::endl << std::endl;
    return 0;
}

void welcome() {
    //simple welcome and instruction
    std::cout << "\n\nWelcome to Tic Tac Toe!\n\n"
              << "Two players\n(Player 1: O)\n(Player 2: X)\nwill fill out the 3x3 "
              << "grid until a player has 3 spaces in a row.\n"
              << "(Horizontal, Vertical, Diagonal)\n\n"
              << "Press enter if you are ready to play: ";
    std::cin.ignore();
}

void print_spaces() {
    //prints 50 spaces
    for (int i = 0; i < NUM_SPACES; i++) {
        std::cout << std::endl;
    }
}

void print_grid(char icons[][MAX_Y_INDEX]) {
    for (int i = 0; i < MAX_X_INDEX; i++) {
        //prints appropriate icon in each box
        for (int j = 0; j < MAX_Y_INDEX - 1; j++) {
            std::cout << SPACE << icons[i][j] << SPACE << '|';
        }
        std::cout << SPACE << icons[i][MAX_Y_INDEX - 1] << SPACE
                  << std::endl;

        //prints a line after each row for readability (except after row 3)
        if (i < MAX_X_INDEX - 1) {
            for (int k = 0; k < LINES; k++) {
                std::cout << '-';
            }
            std::cout << std::endl;
        }
    }
}

void print_reminder() {
    //tells users how to input coordinates
    std::cout << "(Coordinates for the grid are zero indexed. Please access by:)\n";
    for(int i = 0; i < MAX_X_INDEX; i++) {
        for(int j = 0; j < MAX_Y_INDEX; j++) {
            std::cout << '[' << i << ',' << j << ']' << SPACE;  
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void take_turn(char icons[][MAX_Y_INDEX], bool &turn) {
    int x_index = -1;
    int y_index = -1;
    bool is_taken_space = true;

    if (turn) {
        std::cout << "O's, ";
    } else {
        std::cout << "X's, ";
    }
    std::cout << "it's your turn.\n";

    //Loops until user inputs a space that is not taken
    while (is_taken_space) {

        //Accepts x index
        while (x_index > MAX_X_INDEX - 1 || x_index < 0) {
            std::cout << "Input the x coordinate: ";
            std::cin >> x_index;
        }

        //Accepts y index
        while (y_index > MAX_Y_INDEX - 1 || y_index < 0) {
            std::cout << "Input the y coordinate: ";
            std::cin >> y_index;
        }

        //Error check if the coordinate values are out of bounds (less than 0 or more
        //than 2).
        if (x_index > MAX_X_INDEX - 1 || x_index < 0 || y_index > MAX_Y_INDEX - 1
        || y_index < 0) {
            std::cout << "Invalid input. " << std::endl;
        }

        //checks if the space is taken
        if (icons[x_index][y_index] == ' ') {
            is_taken_space = false;
        } else {
            std::cout << "Coordinate taken. " << std::endl << std::endl;
            x_index = -1;
            y_index = -1;
        }
    }

    //switch players
    if (turn) {
        icons[x_index][y_index] = 'O';
        turn = false;
    } else {
        icons[x_index][y_index] = 'X';
        turn = true;
    }
}

bool check_win_cond (char icons[][MAX_Y_INDEX], int &winner) {
    int x_count = 0;
    int o_count = 0;
    int space_count = 0;

    //if all of the spaces are taken stop
    for (int i = 0; i < MAX_X_INDEX; i++) {
        for (int j = 0; j < MAX_Y_INDEX; j++) {
            if (icons[i][j] == ' ') {
                space_count++;
            }
        }
    }

    if (space_count == 0) {
        return false;
    }

    //if three in a row horizontal, win
    for (int i = 0; i < MAX_X_INDEX; i++) {
        x_count = 0;
        o_count = 0;
        for (int j = 0; j < MAX_Y_INDEX; j++) {
            //check if an icon is in the box
            if (icons[i][j] == 'O') {
                o_count++;
            } else if (icons[i][j] == 'X') {
                x_count++;
            }

            //if a certain icon is 3 in a row return false
            if (x_count == 3) {
                winner = 1;
                return false;
            } else if (o_count == 3) {
                winner = 0;
                return false;
            }
        }
    }

    //if three in a row vertical, win
    for (int j = 0; j < MAX_Y_INDEX; j++) {
        x_count = 0;
        o_count = 0;
        for (int i = 0; i < MAX_X_INDEX; i++) {
            //check if an icon is in the box
            if (icons[i][j] == 'O') {
                o_count++;
            } else if (icons[i][j] == 'X') {
                x_count++;
            }

            //if a certain icon is 3 in a row return false
            if (x_count == 3) {
                winner = 1;
                return false;
            } else if (o_count == 3) {
                winner = 0;
                return false;
            }
        }
    }

    //if diagonal ([0,2],[1,1],[2,0]), win
    x_count = 0;
    o_count = 0;
    for (int i = 0; i < MAX_X_INDEX; i++) {
        int j = 2;

        //check if an icon is in the box
        if (icons[i][j] == 'O') {
            o_count++;
        } else if (icons[i][j] == 'X') {
            x_count++;
        }

        //if a certain icon is 3 in a row return false
        if (x_count == 3) {
            winner = 1;
            return false;
        } else if (o_count == 3) {
            winner = 0;
            return false;
        }
        j--;
    }

    //if diagonal ([0,0],[1,1],[2,2]), win
    x_count = 0;
    o_count = 0;
    for (int i = 0; i < MAX_X_INDEX; i++) {
        
        //check if an icon is in the box
        if (icons[i][i] == 'O') {
            o_count++;
        } else if (icons[i][i] == 'X') {
            x_count++;
        }

        //if a certain icon is 3 in a row return false
        if (x_count == 3) {
            winner = 1;
            return false;            
        } else if (o_count == 3) {
            winner = 0;
            return false;
        }
    }
    return true;
}

bool check_to_replay(int winner, int &o_counter, int &x_counter) {
    char input = YES;
    std::cout << std::endl << "The winner is ";
    //count up wins respectfully
    if (winner == 0) {
        std::cout << "O's.\n";
        o_counter++;
    } else if (winner == 1) {
        std::cout << "X's.\n";
        x_counter++;
    } else {
        std::cout << "nobody.\n";
    }

    std::cout << std::endl << "O's have won " << o_counter << " times\n"
              << "X's have won " << x_counter << " times\n";

    //check if the user wants to replay the game
    while(std::tolower(input) == YES) {
        std::cout << "Would you like to play again? (Y/N): ";
        std::cin >> input;
        if (std::tolower(input) == YES) {
            return true;
        }
    }
    return false;
}

void clear_grid (char icons[][MAX_Y_INDEX]) {
    //all the boxes back into spaces
    for (int i = 0; i < MAX_X_INDEX; i++) {
        for (int j = 0; j < MAX_Y_INDEX; j++) {
            icons[i][j] = ' ';
        }
    }
}