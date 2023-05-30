// Bryan Kim
// list.cpp
// This header file defines the members, methods, and constructors/destructor
// for the TodoList class.
// (Note: lower may not be implemented.)

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

// desc: Copy constructor for the TodoList class
// pre : -other TodoList must exist
// post: -Copy TodoList points to the list of the original
TodoList::TodoList(TodoList const &other) {
    head = other.head;
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

// desc: Accepts a string entry and removes all entries from the list that exactly
//       contain that string
// pre : -Must have prior added entries
// post: -All entries with "text" are deleted from the list
//       -Linked list must stay linked after elements are removed
void TodoList::remove_entry(string text) {
    EntryNode *iter = head;
    // while the next node is still part of the list
    while (iter->next != nullptr) {
        // remove if the next matches the text, iterate after
        if (iter->next->text == text) {
            EntryNode *temp = iter->next->next;
            delete iter->next;
            iter->next = temp;
            // iterate
        } else {
            iter = iter->next;
        }
    }
}

// desc: Accepts a string entry and moves all entries in the list that exactly contain that
//       string up by one entry. However, if the first entry in the list matches entry,
//       then none of the matching elements are raised.
// pre : none
// post: -All entries with "text" are brought up one in the list
//       -If a matching entry is already on the top, nothing happens
void TodoList::raise(string text) {
    // check if target text needs to be moved to top
    if (head->next->text == text) {
        // top = the node you swap with
        // target = the target node to raise
        // after = node after the pair
        EntryNode *top    = head;
        EntryNode *target = head->next;
        EntryNode *after  = head->next->next;
        target->next      = top;
        top->next         = after;
        head              = target;
    }

    // check between two texts (target and top) and swap them
    // update pointers around them accordingly
    EntryNode *iter = head;
    while (iter->next->next != nullptr) {
        if (iter->next->next->text == text) {
            // top = the node you swap with
            // target = the target node to raise
            // before = node before the pair
            // after = node after the pair
            EntryNode *before = iter;
            EntryNode *top    = iter->next;
            EntryNode *target = iter->next->next;
            EntryNode *after  = iter->next->next->next;
            before->next      = target;
            target->next      = top;
            top->next         = after;
        }
        iter = iter->next;
    }
}

// desc: Accepts a string entry and moves all entries in the list that exactly contain that
//       string down by one entry. However, if the last entry in the list matches entry,
//       then none of the matching elements are raised.
// pre : none
// post: -All entries with "text" are brought down one on the list
//       -If a matching entry is already on the bottom, nothing happens
void TodoList::lower(string text) {
    // is the bottom lowerable
    // before -> moved -> top -> bottom -> after

    /*
    EntryNode *iter = head;
    int pre = 0;
    int after = 0;
    int count = 0;
    while (iter->next != nullptr) {
        pre = count;
        after = count;
        if (iter->next->text == text) {
            iter = iter->next;
            while (iter->next->text == text) {
                iter = iter->next;
                after++;
            }
            EntryNode *moved = remove(after);
            insert(pre, moved);
        } else {
            iter = iter->next;
        }
        count++;
    }
    */
}

// desc: Accepts a string entry and marks all entries in the list that exactly contain that
//       string as "checked"
// pre : -Must have prior added entries
// post: -Changes the .checked to true
void TodoList::check(string text) {
    for (EntryNode *iter = head; iter != nullptr; iter = iter->next) {
        // if node's text = target, check its box
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
        // if node's text = target, uncheck its box
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
        cout << "[" << check << "] " << iter->text << endl;
    }
}