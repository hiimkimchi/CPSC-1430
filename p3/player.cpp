// Bryan Kim
// player.cpp
// This file defines the methods and constructors for the Board class

#include "player.h"

// desc: Constructs the Player object
// pre : none
// post: -symbol is initialized to ' '
//       -points is initialized to 0
Player::Player() {
    symbol = ' ';
    points = 0;
}

// desc: Gets symbol of Player
// pre : -symbol must be initialized;
// post: -return symbol
char Player::get_symbol() {
    return symbol;
}

// desc: Set symbol of Player
// pre : none
// post: -set symbol to desired symbol
void Player::set_symbol(char symbol) {
    this->symbol = symbol;
}

// desc: Gets points of Player
// pre : -points must be initialized
// post: -return points
unsigned int Player::get_points() {
    return points;
}

// desc: Increments points of Player
// pre : -points must be initialized
// post: -points increased by 1
void Player::award_point() {
    points++;
}