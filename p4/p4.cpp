// Bryan Kim
// p4.cpp
// This file implements linked lists in a To Do List application.
// Users will be able to use an assortment of functions to tell
// the application to add, remove, raise, check, and uncheck nodes.
// (Note: lower method may not be implemented)

#include "list.h"
#include <iostream>

using namespace std;

char const QUIT    = 'Q';
char const ADD     = '+';
char const REMOVE  = '-';
char const RAISE   = '^';
char const LOWER   = 'v';
char const CHECK   = '>';
char const UNCHECK = '<';

// desc: Uses a while loop to show users the list and accept a command
// pre : -Initialize the list state as an empty list
// post: none
int main() {
    char     input_char = ' ';
    int      line_length;
    string   input_str;
    TodoList list;

    cout << endl
         << endl
         << "Enter (COMMAND) (ITEM)" << endl
         << endl
         << "COMMANDS: Q(quit), +(add), -(remove), ^(raise), >(check), <(uncheck)";
    // while the command isnt 'Q'
    while (input_char != QUIT) {
        // show list and get user input
        list.show();
        cin >> input_char;
        getline(cin, input_str);
        line_length = input_str.size();
        // if string is not blank, check for commands
        if (line_length > 0) {
            if (input_char == ADD) {
                list.add_entry(input_str);
            } else if (input_char == REMOVE) {
                list.remove_entry(input_str);
            } else if (input_char == RAISE) {
                list.raise(input_str);
            } else if (input_char == LOWER) {
                list.lower(input_str);
            } else if (input_char == CHECK) {
                list.check(input_str);
            } else if (input_char == UNCHECK) {
                list.uncheck(input_str);
            } else {
                cout << endl << "Invalid command. Please select a valid command.\n\n";
            }
        } else {
            if (input_char != QUIT) {
                cout << endl << "Invalid command. Please select a valid command.\n\n";
            }
        }
        cout << endl;
    }
    cout << "Thank you for using the To-Do List Editor.\n\n";
    return 0;
}