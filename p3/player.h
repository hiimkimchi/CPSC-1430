// Bryan Kim
// player.h
// This header file sets the members, methods, and constructors
// for the Player class.

// invariants:
//-must include in player.cpp for definitions
//-symbol will either be ' ', 'X', or 'O'
//-points will always be 0 or positive (unsigned)
//-symbol is not a whitespace or control character

#ifndef PLAYER
#define PLAYER

class Player {
    private:
    // members
    char         symbol;
    unsigned int points;

    public:
    // constructor
    Player();

    // methods
    void         set_symbol(char symbol);
    char         get_symbol();
    unsigned int get_points();
    void         award_point();
};

#endif
