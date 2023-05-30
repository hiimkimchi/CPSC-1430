// Bryan Kim
// board.h
// This header file sets the members, methods, and constructors/destructor
// for the Board class.

// invariants:
//-must include in board.cpp for definitions
//-squares is either null, or pointing to a dynamically allocated 2D array
//-The height and width of the array is size (square grid)
//-Every character element in the 2D array pointed by squares is not a
//  whitespace or control character

#include "player.h"

class Board {
    private:
    // members
    char **squares;
    int    size;

    public:
    // constructor
    Board(int size);

    // methods
    void display();
    bool is_full();
    bool is_winner(Player player);
    bool set_element(int x, int y, char symbol);

    // destructor
    ~Board();
};