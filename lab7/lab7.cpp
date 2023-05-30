// Bryan Kim
// lab7.cpp
// I stole this code from Dr. Cuneo (so did the rest of the class).
// This file takes the "Tracer" class and implements it in the code by telling when
// lifetimes start and end.

#include "tracer.h"

// desc : Allocates and returns an array of Tracer instances
// pre  : `count` must be a non-negative value
// post : Returns a pointer to a newly allocated array of Tracer
//        instances with exactly `count` elements.
Tracer *make_tracer_array(int count) {
    Tracer tracer = "make_tracer_array";
    return new Tracer[count];
}

// desc : Deallocates the array pointed by the input pointer
// pre  : `array_ptr` must point to a valid, dynamically allocated
//        array in memory
// post : Deallocates the array pointed by `array_ptr`
void delete_tracer_array(Tracer *array_ptr) {
    Tracer tracer = "delete_tracer_array";
    delete[] array_ptr;
}

// Type invariants: None
struct TracerTriplet {
    Tracer a;
    Tracer b;
    Tracer c;
};

Tracer const STATIC_TRACER = "static";

// desc : Demonstrates the behavior of the implemented `Tracer` class
// pre  : None
// post : None, aside from description
int main() {

    Tracer main_tracer = "main";

    // Make a dynamic array and rename its elements
    Tracer *array_ptr = make_tracer_array(4);
    array_ptr[0]      = "0";
    array_ptr[1]      = "1";
    array_ptr[2]      = "2";
    array_ptr[3]      = "3";

    // Showing how initializer arrays act as inputs for
    // each constructor call that is ran.
    Tracer local_array[] = {"zero", "one", "two"};

    // Testing different assignments
    Tracer local_default;
    local_default = main_tracer;
    local_default = *local_array;
    *local_array  = *(local_array + 1);

    // Showing the difference between copy construction
    // and copy assignment.
    TracerTriplet triplet        = {"a", "b", "c"};
    TracerTriplet second_triplet = triplet;
    TracerTriplet third_triplet  = {"x", "y", "z"};
    third_triplet                = triplet;

    delete_tracer_array(array_ptr);

    return 0;
}
