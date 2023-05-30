// Bryan Kim
// lab8.cpp
// This file allocates both a stack and dynamic linked list that
// hold letters in them

#include <iostream>

// desc: A unit of a linked list of strings. Stores a string,
//       with a pointer to the next node (if any)
// invariants:
//      -`next` always either points to a valid `Node`
//      instance, or is null
struct Node {
    std::string name;
    Node       *next;
};

// desc: Prints a linked list
// pre : -Node *head must exist and must have a corresponding list
// post: none
void print(Node *&head);

// desc: Makes a linked list where each node represents a letter in
//       the alphabet
// pre : -Node *head must exist
//       -Node *head cannot point to another list for the function
//        to work properly
// post: -Allocates a linked list with 26 nodes (for each letter)
void make_alpha_list(Node *&head);

// desc: Deallocates the linked list headed by *head
// pre : -linked list pointed by head must be allocated
// post: -linked list pointed by head must be deallocated
void deallocate(Node *&head);

// desc: Allocates two linked lists, prints them, and deallocates them
// pre : none
// post: -All allocated lists are deallocated
int main() {
    // initialize heads
    // STACK
    Node *head_first = nullptr;
    // DYNAMIC
    Node *head_second = nullptr;

    // add nodes to first list
    Node d     = {"d", nullptr};
    Node c     = {"c", &d};
    Node b     = {"b", &c};
    Node a     = {"a", &b};
    head_first = &a;

    // initialize and set the head_second list
    make_alpha_list(head_second);

    // print the first list
    print(head_first);

    // print the second list
    print(head_second);

    // deallocate the dynamic linked list
    deallocate(head_second);

    return 0;
}

void print(Node *&head) {
    std::cout << std::endl;
    // start at head, traverse through the list and print
    for (Node *iter = head; iter != nullptr; iter = iter->next) {
        std::cout << iter->name << ' ';
    }
    std::cout << std::endl;
}

void make_alpha_list(Node *&head) {
    for (char letter = 'z'; letter >= 'a'; letter--) {
        // allocate temp, point it to the next node (link it)
        // set the letter to current letter, set head to temp
        Node *temp = new Node;
        temp->next = head;
        temp->name = letter;
        head       = temp;
    }
}

void deallocate(Node *&head) {
    // set a temporary Node* to next in the list
    // delete current, set current to next (temporary)
    while (head != nullptr) {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}