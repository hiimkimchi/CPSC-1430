// Bryan Kim
// list.h
// This header file sets the members, methods, and constructors/destructor
// for the TodoList class.

// invariants:
//-tails of the linked list must point to nullptr

using namespace std;
#include <string>

struct EntryNode {
    bool       checked;
    string     text;
    EntryNode *next;
};

class TodoList {
    private:
    EntryNode *head;

    public:
    // constructors/deconstructor
    TodoList();
    ~TodoList();

    void add_entry(string text);
    void check(string text);
    void uncheck(string text);
    void show();
};