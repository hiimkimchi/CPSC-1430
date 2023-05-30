// Bryan Kim
// queue.h
// This header file sets the members, methods, and constructors/destructor
// for the Queue class.

struct Node {
    int   data;
    Node *next;
};

class Queue {
    private:
    Node *head;
    int   size;

    public:
    Queue();
    Queue(Queue const &other);
    ~Queue();
    void operator=(Queue const &other);
    void enqueue(int value);
    int  dequeue();
    int  get_size();
};