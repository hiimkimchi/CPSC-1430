// Bryan Kim
// lab2.cpp
// This file takes two inputted strings, prints them, swaps, prints, swaps
// again, and prints again.

#include <iostream>

//desc: requests two string inputs from user and returns both
//pre : requires two string variables to already exist in the function 
//      calling this one
//post: returns by passby reference
void input(std::string &first, std::string &second);

//desc: swaps two inputed referenced string
//pre : both strings must exist in the function calling this one
//post: returns by passby reference
void swap_strings(std::string &first, std::string &second);

//desc: prints both strings, differentiated by a space in between
//pre : none
//post: none
void output(std::string first, std::string second);

//desc:
//pre :
int main() {
    std::string first;
    std::string second;
    input(first,second);
    output(first,second);
    swap_strings(first,second);
    output(first,second);
    swap_strings(first,second);
    output(first,second);
    return 0;
}

void input(std::string &first, std::string &second) {
    std::cout << std::endl << "Hello, input the first string: " << std::endl;
    getline(std::cin, first);
    std::cout << std::endl << "Second string: " << std::endl;
    getline(std::cin, second);
    std::cout << std::endl << std::endl;
}

void swap_strings(std::string &first, std::string &second) {
    std::string temp = first;
    first = second;
    second = temp;
}

void output(std::string first, std::string second) {
    std::cout << first << ' ' << second;
    std::cout << std::endl << std:: endl;
}