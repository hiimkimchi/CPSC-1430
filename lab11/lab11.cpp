// Bryan Kim
// lab11.cpp
// This file is the main file for lab11. It should implement the
// Queue class made in queue.h/.cpp
// Testing will be extremely similar to lab10

#include "queue.h"
#include <iostream>

using namespace std;

//
//
//
void enqueue_10(Queue &test);

//
//
//
void dequeue_all(Queue &test);

//
//
//
int main() {
    int   current_val;
    Queue test = Queue();
    test.dequeue();
    enqueue_10(test);

    Queue test_copy  = test;
    Queue test_ccopy = Queue(test);

    // should print 0 and 1
    current_val = test.dequeue();
    cout << current_val << endl;
    current_val = test.dequeue();
    cout << current_val << endl << endl;

    dequeue_all(test);
    dequeue_all(test_copy);
    dequeue_all(test_ccopy);

    return 0;
}

void enqueue_10(Queue &test) {
    for (int i = 0; i < 10; i++) {
        test.enqueue(i);
    }
}

void dequeue_all(Queue &test) {
    // get size
    int size = test.get_size();
    int dqd;

    // pop all them out
    for (int i = 0; i < size; i++) {
        dqd = test.dequeue();
        cout << dqd << endl;
    }
    cout << endl;
}