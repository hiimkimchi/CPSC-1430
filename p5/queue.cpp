// Bryan Kim
// queue.cpp
// This header file defines the members, methods, and constructors/destructor
// for the Queue class.

#include "queue.h"
#include <iostream>

using namespace std;

// desc: Default constructor for the Queue class
// pre : -Node struct must be defined and implemented into the class
// post: -Queue object must be created
Queue::Queue() {
    head = nullptr;
    size = 0;
}

// desc: Copy constructor for the Queue class
// pre : -other Queue object must exist
// post: -Copy Queue points to the list of the original
Queue::Queue(Queue const &other) {
    head  = nullptr;
    size  = 0;
    *this = other;
}

// desc: Destructor for the Queue class
// pre : -Queue object must exist with allocated links
// post: -Queue object and its links must be deallocated
Queue::~Queue() {
    while (head != nullptr) {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
}

// desc: Overloaded assignment operator for the Queue class
// pre : -other Queue must exist
// post: -both copy Queue and other Queue will be identical
//       -both will have seperate pointers (different in memory)
void Queue::operator=(Queue const &other) {
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

// desc: Enqueue a value to the top of the list
// pre : none
// post: -new node added at the head of the linked list
void Queue::enqueue(int value) {
    Node *temp = new Node;
    temp->next = head;
    temp->data = value;
    head       = temp;
    size++;
}

// desc: Dequeue a value from the tail of the list
// pre : -size must be > 0 for a dequeue to actually occur
// post: -node deleted from the tail of the linked list
//       -throws an error if the queue is empty
int Queue::dequeue() {
    int dq_val = -1;

    if (size > 0) {
        // check if the queue has a size of 1
        // and remove the node accordingly
        if (head->next == nullptr) {
            dq_val = head->data;
            delete head;
            head = nullptr;
            size--;
            return dq_val;
        }

        // if not, iterate to the end and remove the last node
        Node *iter = head;
        while (iter->next->next != nullptr) {
            iter = iter->next;
        }
        dq_val = iter->next->data;
        delete iter->next;
        iter->next = nullptr;
        // if size of queue = 0
    } else {
        throw std::runtime_error("Queue is empty, runtime error thrown.");
    }
    size--;
    return dq_val;
}

// desc: Gets size
// pre : none
// post: -returns size
int Queue::get_size() {
    return size;
}