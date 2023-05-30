#include "tracer.h"
#include <iostream>

// desc: Default Constructor
// pre : none
// post: name member is modified
Tracer::Tracer() {
    name = "default";
    std::cout << "lifetime of \'" << name << "\' started\n";
}

// desc: Copy Constructor
// pre : none
// post: name member is modified
Tracer::Tracer(Tracer const &other) {
    name = other.name + ' ' + "copy";
    std::cout << "lifetime of \'" << name << "\' started\n";
}

// desc: Converting Constructor
// pre : none
// post: name member is modified
Tracer::Tracer(char const *name_str) {
    name = name_str;
    std::cout << "lifetime of \'" << name << "\' started\n";
}

// desc: "Assignment" Operator
// pre : none
// post: none
void Tracer::operator=(Tracer const &other) {
    std::cout << "tracer \'" << name << "\' renamed to \'" << other.name << "\'.\n";
}

// desc: Assignment Operator
// pre : none
// post: name member is modified
void Tracer::operator=(char const *new_name) {
    std::cout << "tracer \'" << name << "\' renamed to \'" << new_name << "\'.\n";
    name = new_name;
}

// desc: Destructor
// pre : none
// post: none
Tracer::~Tracer() {
    std::cout << "lifetime of \'" << name << "\' ended\n";
}