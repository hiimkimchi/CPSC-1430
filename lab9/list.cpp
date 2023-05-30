// Bryan Kim
// list.cpp
// This header file defines the members, methods, and constructors/destructor
// for the TodoList class.

#include "list.h"
#include <iostream>
#include <string>

using namespace std;

// desc: Default constructor for the TodoList class
// pre : -EntryNode struct must be defined and implemented into the class
// post: -TodoList object created
TodoList::TodoList() {
    head = nullptr;
}

// desc: Destructor for the TodoList class
// pre : -TodoList object must exist with allocated links
// post: -TodoList object and its links must be deallocated
TodoList::~TodoList() {
    while (head != nullptr) {
        EntryNode *temp = head->next;
        delete head;
        head = temp;
    }
}

// desc: Accepts a string entry and adds an entry containing the string's
//       text to the end of the list.
// pre : none
// post: -A node containing new text must be linked to the list at the end
void TodoList::add_entry(string text) {
    EntryNode *temp = new EntryNode;
    temp->next      = head;
    temp->text      = text;
    temp->checked   = false;
    head            = temp;
}

// desc: Accepts a string entry and marks all entries in the list that exactly contain that
//       string as "checked"
// pre : -Must have prior added entries
// post: -Changes the .checked to true
void TodoList::check(string text) {
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        if (iter->text == text) {
            iter->checked = true;
        }
    }
}

// desc: Accepts a string entry and marks all entries in the list that exactly contain that
//       string as "unchecked"
// pre : -Must have prior added entries
// post: -Changes the .checked to false
void TodoList::uncheck(string text) {
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        if (iter->text == text) {
            iter->checked = false;
        }
    }
}

// desc: Prints the linked list pointed by the TodoList object
// pre : none
// post: none
void TodoList::show() {
    char check = ' ';
    cout << endl << endl;
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        check = ' ';
        if (iter->checked) {
            check = 'X';
        }
        cout << "[" << check << "]  " << iter->text << endl;
    }
}