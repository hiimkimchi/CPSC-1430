// Bryan Kim
// lab10.cpp
// This file is the main file for lab10. It should implement the
// Stack class made in stack.h/.cpp

#include "stack.h"
#include <iostream>

using namespace std;

// desc: Pushes integers 0-9 down a stack
// pre : -stack must be constructed
// post: -stack will have 10 integers in it (9 will be the Last In)
void push_10(Stack &test);

// desc: Pops each integer out one by one and prints each time
// pre : -stack must be constructed
// post: -stack will be empty and for this lab, should print integers
//        from 9-0.
void pop_all(Stack &test);

// desc: Tests that the Stack class's methods are functional
// pre : -INVARIANT: must include "stack.h" for all functions (including main)
// post: -will print three identical stacks ("9-0"), but they will all be constructed
//        in different ways (default, copy, overloaded assignment operator)
int main() {
    Stack test = Stack();

    push_10(test);

    Stack test_copy  = test;
    Stack test_ccopy = Stack(test);

    pop_all(test);
    pop_all(test_copy);
    pop_all(test_ccopy);

    return 0;
}

void push_10(Stack &test) {
    // pushes 0-10 into the stack
    for (int i = 0; i < 10; i++) {
        test.push(i);
    }
}

void pop_all(Stack &test) {
    // get size
    int size = test.get_size();
    int popped;

    // pop all them out
    for (int i = 0; i < size; i++) {
        popped = test.pop();
        cout << popped << endl;
    }
    cout << endl;
}