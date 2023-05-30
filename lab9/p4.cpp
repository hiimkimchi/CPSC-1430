// Bryan Kim
// p4.cpp (lab9)
// This file uses list.o to implement p4 PARTIALLY
// (since this is actually lab9)

#include "list.h"
#include <iostream>

using namespace std;

char const QUIT    = 'Q';
char const ADD     = '+';
char const CHECK   = '>';
char const UNCHECK = '<';

// desc: Uses a while loop to show users the list and accept a command
// pre : -Initialize the list state as an empty list
// post: none
int main() {
    char     input_char = ' ';
    string   input_str;
    TodoList list;
    while (input_char != QUIT) {
        list.show();
        cin >> input_char;
        // not sure if this will work
        getline(cin, input_str);
        if (input_char == ADD) {
            list.add_entry(input_str);
        } else if (input_char == CHECK) {
            list.check(input_str);
        } else if (input_char == UNCHECK) {
            list.uncheck(input_str);
        } else {
            if (input_char != QUIT) {
                cout << "Invalid command. Please select a valid command.\n\n";
            }
        }
        cout << endl;
    }
    cout << "Thank you for using the To-Do List Editor.\n\n";
    return 0;
}