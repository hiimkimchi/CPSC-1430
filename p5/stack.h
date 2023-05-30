// Bryan Kim
// stack.h
// This header file sets the members, methods, and constructors/destructor
// for the Stack class.

struct StackNode {
    int        data;
    StackNode *next;
};

class Stack {
    private:
    StackNode *head;
    int        size;

    public:
    Stack();
    Stack(Stack const &other);
    ~Stack();
    void operator=(Stack const &other);
    void push(int value);
    int  pop();
    int  get_size();
};