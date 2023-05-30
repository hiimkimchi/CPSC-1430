// Bryan Kim
// p5.cpp
// This file interprets expressions in Reverse Polish Notations
// it will include the queue and stack classes to help

#include "queue.h"
#include "stack.h"
#include <iostream>

// OpId is an enum (short for enumeration). Enums assign names
// to integer values, allowing us to map things to a set of
// integer identifiers
enum OpId {
    BAD  = 0, // Does not correspond to any operation
    ADD  = 1,
    SUB  = 2,
    MUL  = 3,
    DIV  = 4,
    TOP  = 5,
    POP  = 6,
    DUP  = 7,
    COND = 8,
    ENQ  = 9,
    DEQ  = 10,
    SAVE = 11,
    LOAD = 12,
    END  = 1024
};

// To represent the mapping between operations and their string
// representation, we will make this helper struct to act as an
// entry in our list of mappings
struct Operation {
    std::string name;
    OpId        id;
};

// The mapping of operation string representations to their
// integer id
Operation const OPERATIONS[] = {
    {"add", ADD},
    {"sub", SUB},
    {"mul", MUL},
    {"div", DIV},
    {"top", TOP},
    {"pop", POP},
    {"dup", DUP},
    {"cond", COND},
    {"enq", ENQ},
    {"deq", DEQ},
    {"save", SAVE},
    {"load", LOAD},
    {"end", END},
};

// The number of entries in the operation id mapping, calculated
// by taking the quotient of the total size of the mapping by
// the size of each entry.
int const OPERATION_COUNT = sizeof(OPERATIONS) / sizeof(Operation);

// desc : Maps token strings to ther corresponding operation IDs, if
//        possible.
// pre  : None
// post : If the input token corresponds to a valid string representation
//        for an operation, the corresponding OpId value is returned. If
//        no such matching exists, OpId::BAD is returned instead
OpId token_to_operation_id(std::string token) {
    for (int i = 0; i < OPERATION_COUNT; i++) {
        // Linear search through entries until a match is found...
        if (OPERATIONS[i].name == token) {
            return OPERATIONS[i].id;
        }
    }
    // ... or until we run out of entries
    return OpId::BAD;
}

// desc : Returns true if and only if the input string represents a non-empty
//        string consisting only of roman numerals.
// pre  : None
// post : None, aside from description
bool is_numeric(std::string token) {
    int size = token.size();
    // In the odd case we get an empty string, we count it as *not* an integer
    if (size == 0) {
        return false;
    }
    // Iterate through token, double-checking that the character values are only
    // in the valid range for digits
    for (int i = 0; i < size; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    return true;
}

// desc: Pop the top-most value of the stack, B, and the next-top-most value of the stack, A, and push the value A+B
//       onto the stack.
// pre : -stack must exist with at least two values for it to work properly
// post: -stack will have one less node.
void add(Stack &active_stack) {
    int first_val  = active_stack.pop();
    int second_val = active_stack.pop();
    active_stack.push(first_val + second_val);
}

// desc: Pop the top-most value of the stack, B, and the next-top-most value of the stack, A, and push the value A-B
//       onto the stack.
// pre : -stack must exist with at least two values for it to work properly
// post: -stack will have one less node.
void subtract(Stack &active_stack) {
    int first_val  = active_stack.pop();
    int second_val = active_stack.pop();
    active_stack.push(second_val - first_val);
}

// desc: Pop the top-most value of the stack, B, and the next-top-most value of the stack, A, and push the value A*B
//       onto the stack.
// pre : -stack must exist with at least two values for it to work properly
// post: -stack will have one less node.
void multiply(Stack &active_stack) {
    int first_val  = active_stack.pop();
    int second_val = active_stack.pop();
    active_stack.push(first_val * second_val);
}

// desc: Pop the top-most value of the stack, B, and the next-top-most value of the stack, A, and push the value A/B
//       onto the stack.
// pre : -stack must exist with at least two values for it to work properly
//       -divisor must != 0 for it to perform properly
// post: -stack will have one less node.
void divide(Stack &active_stack) {
    int first_val  = active_stack.pop();
    int second_val = active_stack.pop();
    if (first_val == 0) {
        active_stack.push(second_val);
        std::cout << "Cannot divide by 0" << std::endl;
    } else {
        active_stack.push(second_val / first_val);
    }
}

// desc: Print the top-most value of the stack, followed by a newline. This operation preserves the printed value at the
//       top of the stack.
// pre : -stack must exist with at least two values for it to work properly
//       -divisor must != 0 for it to perform properly
// post: -stack will have one less node.
void print_top(Stack &active_stack) {
    int popped = active_stack.pop();
    std::cout << popped << std::endl << std::endl;
    active_stack.push(popped);
}

// desc: Copy the top-most value of the stack, placing the copy on top of the original value on the stack.
// pre : -stack must exist with at least one value for it to work properly
// post: -stack will have one more node
void duplicate(Stack &active_stack) {
    int popped = active_stack.pop();
    active_stack.push(popped);
    active_stack.push(popped);
}

// desc: Pop the three top-most values in the stack, C, B, and A, (shown here from top-most to bottom-most), then place
//       A on the top of the stack if C is non-zero or place B on the top of the stack if C is exactly zero.
// pre : -stack must exist with at least three values for it to work properly
// post: -stack will have two less nodes
void condition(Stack &active_stack) {
    int cond       = active_stack.pop();
    int second_val = active_stack.pop();
    int third_val  = active_stack.pop();
    if (cond == 0) {
        active_stack.push(second_val);
    } else {
        active_stack.push(third_val);
    }
}

// desc : Evaluates command if the command exists (and it isn't save or load)
// pre  : -stack must have one or more node for functions to work properly
// post : -performs functions, saves into the active_stack and active_queue (passby)
void evaluate(Stack &active_stack, Queue &active_queue, std::string token) {
    if (is_numeric(token)) {
        // Convert the token to its integer value
        int value = stoi(token);
        // Push to the stack
        active_stack.push(value);
    } else {
        // It is advised you use the provided OpId enumeration and id mapping
        // functions to switch between your function calls. Of course, not all
        // operations must be handled here, since the end/save/load operations
        // have special requirements that are easier to meet in the main function
        switch (token_to_operation_id(token)) {
        case OpId::ADD:
            add(active_stack);
            break;
        case OpId::SUB:
            subtract(active_stack);
            break;
        case OpId::MUL:
            multiply(active_stack);
            break;
        case OpId::DIV:
            divide(active_stack);
            break;
        case OpId::TOP:
            print_top(active_stack);
            break;
        case OpId::POP:
            active_stack.pop();
            break;
        case OpId::DUP:
            duplicate(active_stack);
            break;
        case OpId::COND:
            condition(active_stack);
            break;
        case OpId::ENQ:
            active_queue.enqueue(active_stack.pop());
            break;
        case OpId::DEQ:
            active_stack.push(active_queue.dequeue());
            break;
        // The case below should happen if an invalid id (like OpId::BAD) is
        // yielded by the id mapping function
        default:
            std::cout << "Unrecognized token '" << token << "'\n";
        }
    }
}

// desc : runs the calculator. If user does not want to end, save, or load, performs an operation in the
//        evaluate function
// pre  : -include "stack.h" and "queue.h"
// post : none
int main() {
    Stack       active_stack;
    Queue       active_queue;
    Stack       save_stack;
    Queue       save_queue;
    std::string token;
    while (std::cin >> token) {
        if (token == "end") {
            // To get the automatic memory cleanup from the Stack/Queue
            // destructors, we must terminate by returning normally from main
            return 0;
        } else if (token == "save") {
            save_stack = active_stack;
            save_queue = active_queue;
        } else if (token == "load") {
            active_stack = save_stack;
            active_queue = save_queue;
        } else {
            // to prevent main from becoming too large/complex, we delegate the
            // evaluation of "non-special" operations to a separate function
            evaluate(active_stack, active_queue, token);
        }
    }
}
