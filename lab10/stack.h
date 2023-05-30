// Bryan Kim
// stack.h
// This header file sets the members, methods, and constructors/destructor
// for the Stack class.

struct Node {
    int   data;
    Node *next;
};

class Stack {
    private:
    Node *head;
    int   size;

    public:
    Stack();
    Stack(Stack const &other);
    ~Stack();
    void operator=(Stack const &other);
    void push(int value);
    int  pop();
    int  get_size();
};