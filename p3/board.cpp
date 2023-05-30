// Bryan Kim
// board.cpp
// This file defines methods, constructors, and destructor of the
// Board class.

#include "board.h"
#include <iostream>

char const SPACE = ' ';
int const  LINES = 4;

// desc: Constructs the Board object
// pre : -size must be > 0
// post: -size member is initialized to desired size
//       -2D dynamic array is allocated
//       -each element of the allocated array is initialized to ' '
Board::Board(int size) {
    this->size = size;

    // allocate array
    squares = new char *[size];
    for (int i = 0; i < size; i++) {
        squares[i] = new char[size];
    }

    // initialize each element to ' '
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            squares[i][j] = SPACE;
        }
    }
}

// desc: Displays the board
// pre : -Board object's members must be initialized
//       -size must be > 0
// post: none
void Board::display() {
    for (int i = 0; i < size; i++) {
        // prints appropriate icon in each box
        for (int j = 0; j < size - 1; j++) {
            std::cout << SPACE << squares[i][j] << SPACE << '|';
        }
        std::cout << SPACE << squares[i][size - 1] << SPACE << std::endl;

        // prints a line after each row for readability (except after last row)
        if (i < size - 1) {
            for (int k = 0; k < (size * LINES) - 1; k++) {
                std::cout << '-';
            }
            std::cout << std::endl;
        }
    }
}

// desc: Checks if the board is full
// pre : -Board object's members must be initialized
//       -size must be > 0
// post: -if there is a ' ' element, return false
//       -if there is no ' ' element, return true
bool Board::is_full() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (squares[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// desc: Checks if player is the winner
// pre : -must include "player.h"
// post: -if the player matched size symbols in a row/col/diag, return true
//       -if the player did not, return false
bool Board::is_winner(Player player) {
    char target = player.get_symbol();
    int  horiz_count;
    int  verti_count;
    int  ldiag_count;
    int  rdiag_count;
    int  k;

    // check each row and col and diag for win
    for (int i = 0; i < size; i++) {
        horiz_count = 0;
        verti_count = 0;
        ldiag_count = 0;
        rdiag_count = 0;
        k           = size - 1;
        // count up each counter variable and if any of them == size
        // return true
        for (int j = 0; j < size; j++) {
            if (squares[i][j] == target) {
                horiz_count++;
            }
            if (squares[j][i] == target) {
                verti_count++;
            }
            if (squares[j][j] == target) {
                ldiag_count++;
            }
            if (squares[j][k] == target) {
                rdiag_count++;
            }

            if (horiz_count == size || verti_count == size || ldiag_count == size || rdiag_count == size) {
                return true;
            }
            k--;
        }
    }
    return false;
}

// desc: Set an element in the 2D array as the provided char
// pre : -x and y are indexes (implemented at zero indexes)
// post: -squares is permanently changed at [x][y]
bool Board::set_element(int x, int y, char symbol) {
    // set the element at [x][y] as symbol
    if (x < size && y < size && squares[x][y] == SPACE) {
        squares[x][y] = symbol;
        return false;
    }
    return true;
}

// desc: Destructs the Board object
// pre : -2D dynamic array must be initialized
// post: -array will be deallocated to prevent memory leak
Board::~Board() {
    for (int i = 0; i < size; i++) {
        delete[] squares[i];
    }
    delete[] squares;
}