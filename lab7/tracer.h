#include <string>

// invariants:
//-include string and iostream

class Tracer {
    private:
    std::string name;

    public:
    Tracer();
    Tracer(Tracer const &other);
    Tracer(char const *name_str);

    void operator=(Tracer const &other);
    void operator=(char const *new_name);

    ~Tracer();
};