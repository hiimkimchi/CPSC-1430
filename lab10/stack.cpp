// Bryan Kim
// stack.cpp
// This header file defines the members, methods, and constructors/destructor
// for the Stack class.

#include "stack.h"
#include <iostream>

using namespace std;

// desc: Default constructor for the Stack class
// pre : -Node struct must be defined and implemented into the class
// post: -Stack object must be created
Stack::Stack() {
    head = nullptr;
    size = 0;
}

// desc: Copy constructor for the Stack class
// pre : -other Stack object must exist
// post: -Copy Stack points to the list of the original
Stack::Stack(Stack const &other) {
    head  = nullptr;
    size  = 0;
    *this = other;
}

// desc: Destructor for the Stack class
// pre : -Stack object must exist with allocated links
// post: -Stack object and its links must be deallocated
Stack::~Stack() {
    while (head != nullptr) {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}

// desc: Overloaded operator for the Stack class
// pre : -other Stack must exist
// post: -both copy stack and other stack will be the same
//       -both will be seperate (wont have pointers overlapping)
void Stack::operator=(Stack const &other) {
    // if the size is 0, default
    if (other.size == 0) {
        head = nullptr;
        size = 0;
        // otherwise copy
    } else {
        // create new head
        head             = new Node;
        Node *copy_iter  = head;
        Node *other_iter = other.head;
        while (other_iter != nullptr) {
            copy_iter->data = other_iter->data;
            other_iter      = other_iter->next;
            // if next iter from other exists, make a new node in copy and iterate
            if (other_iter != nullptr) {
                copy_iter->next = new Node;
                copy_iter       = copy_iter->next;
                // else, iterate
            } else {
                copy_iter->next = nullptr;
            }
        }
        size = other.size;
    }
}

// desc: Push a value to the top of the stack
// pre : none
// post: -new node added at the head of the linked list
void Stack::push(int value) {
    Node *temp = new Node;
    temp->next = head;
    temp->data = value;
    head       = temp;
    size++;
}

// desc: Pop a value from the top of the stack
// pre : -size must be > 0 for a pop to actually occur
// post: -node deleted from the head of the linked list
//       -returns -1 if a node is not popped
int Stack::pop() {
    int popped_val = -1;
    if (size > 0) {
        Node *temp = head->next;
        popped_val = head->data;
        delete head;
        head = temp;
    } else {
        cout << "Stack is empty (returned -1)." << endl;
    }
    size--;
    return popped_val;
}

// desc: Gets size
// pre : none
// post: -returns size
int Stack::get_size() {
    return size;
}