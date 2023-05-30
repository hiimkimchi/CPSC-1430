// Bryan Kim
// lab5.cpp
// This file is a debugging of a previously created code.
// (Fixing memory leaks and functional problems)

#include <iostream>

int const ORIG_LENGTH = 5;
int const INDEX = 4;

// desc : represents a dynamically allocated array of integers stored alongside
//        a count of how many elements it has
// invariants:
//      - `array_ptr` is always either null or pointing to a valid array allocation
//        in dynamic storage
//      - `size` is always set to the number of elements in the array pointed by
//        `array_ptr`
struct DynIntArray {
    int *array_ptr;
    int  size;
};

void        delete_int_array(DynIntArray &int_array);
DynIntArray new_int_array(int size);
void        print_array(DynIntArray &int_array);

// Functions that need to be debugged
DynIntArray copy_int_array(DynIntArray other);
void        resize_int_array(DynIntArray &int_array, int new_size);
int         remove(DynIntArray &int_array, int index);
void        add(DynIntArray &int_array, int index, int value);

// desc : tests the correctness of the functions:
//      - DynIntArray copy_int_array (DynIntArray other);
//      - void resize_int_array(DynIntArray &int_array, int new_size);
//      - int  remove(DynIntArray &int_array, int index);
//      - void add(DynIntArray &int_array, int index, int value);
//
// pre  : None
// post : If any of the tests run find incorrect behavior, it is reported to
//        the user alongside a general description of when/how the incorrect
//        behavior occured.
int main() {
    // Call your unit test functions here
    DynIntArray numba1;
    DynIntArray numba2;
    int removed_val;
    numba1 = new_int_array(ORIG_LENGTH);
    for (int i = 0; i < ORIG_LENGTH; i++) {
        numba1.array_ptr[i] = i;
    }

    numba2 = copy_int_array(numba1);
    removed_val = remove (numba2,INDEX);
    add(numba2, INDEX, removed_val);
    print_array(numba2);
    delete_int_array(numba1);
    delete_int_array(numba2);
    return 0;
}

// desc : deletes the array used by the input `int_array` to store its values
// pre  : `int_array` follows all invariants of DynIntArray
// post :
//      - as stated in the description, deletes the array pointed by the `array_ptr`
//        member of `int_array`, and sets the member to null
//      - sets the `size` of `array_ptr` to zero
//      - does not leak memory
//      - does not access memory out of bounds
void delete_int_array(DynIntArray &int_array) {
    delete[] int_array.array_ptr;
    int_array.array_ptr = nullptr;
    int_array.size      = 0;
}

// desc : returns a new DynIntArray with the corresponding size
// pre  : `size` is not negative
// post :
//      - the `array_ptr` member of the returned value points to a newly allocated int
//        array in dynamic storage with `size` elements
//      - the `size` member of the returned value matches the input `size` value
//      - does not leak memory
//      - does not access memory out of bounds
DynIntArray new_int_array(int size) {
    DynIntArray result;
    result.array_ptr = new int[size];
    result.size      = size;
    return result;
}

// desc : returns a copy of the supplied DynIntArray instance
// pre  : `other` follows all invariants of DynIntArray
// post :
//      - the array pointed by the `array_ptr` member of the return value will be an
//        independent copy of the array pointed by `other.array_ptr`, stored in
//        dynamic memory and with the same size as `other.size`
//      - does not leak memory
//      - does not access memory out of bounds
DynIntArray copy_int_array(DynIntArray other) {
    DynIntArray the_copy;

    // Copy the array from `original`
    the_copy.array_ptr = new int[other.size];

    // Copy the size  from `original
    the_copy.size = other.size;

    // Copies each elements to the new arr
    for (int i = 0; i < the_copy.size; i++) {
        the_copy.array_ptr[i] = other.array_ptr[i];
    }

    // Returns copy of the original
    return the_copy;
}

// desc : changes the size of the input `int_array`
// pre  : `int_array` follows all invariants of DynIntArray
// post :
//      - the `array_ptr` member of `int_array` will point to a newly allocated int array
//        in dynamic storage with the size `new_size`.
//      - all elements from the array originally pointed by `int_array.array_ptr` with an index
//        that also exists in the newly allocated array will be copied over to the same index
//        in that new array
//      - the `size` member of `int_array` will be set to `new_size`
//      - does not leak memory
//      - does not access memory out of bounds
void resize_int_array(DynIntArray &int_array, int new_size) {

    // Allocate new array
    int *new_array_ptr = new int[new_size];

    // Copy over values from old array to new array
    // if the new_size is smaller, copy up to its size
    // if not just copy the availible elements.
    if (new_size > int_array.size) {
        for (int i = 0; i < int_array.size; i++) {
            new_array_ptr[i] = int_array.array_ptr[i];
        }
    } else {
        for (int i = 0; i < new_size; i++) {
            new_array_ptr[i] = int_array.array_ptr[i];
        }
    }

    // Deallocate the arr
    delete[] int_array.array_ptr;

    // Overwrite int_array with new array_ptr and new size
    int_array.array_ptr = new_array_ptr;
    int_array.size      = new_size;
}

// desc : removes the element at index `index` in the array of `int_array`
// pre  : `int_array` follows all invariants of DynIntArray
// post :
//      - the `array_ptr` member of `int_array` will point to a valid array allocation
//        in dynamic storage with the size `int_array.size-1`.
//      - all values except for the one originally at the index `index` will be preserved,
//        in the new array, with element coming after `index` shifted back by one space
//      - does not leak memory
//      - does not access memory out of bounds
int remove(DynIntArray &int_array, int index) {

    // Move every element after index `index` back by one space
    // (initialize return value)
    int removed_element = int_array.array_ptr[index];
    for (int i = index; i < int_array.size - 1; i++) {
        int_array.array_ptr[i] = int_array.array_ptr[i - 1];
    }

    // Resize to remove extra element at the end
    resize_int_array(int_array, int_array.size - 1);

    // Return the removed value
    return removed_element;
}

// desc : inserts `value` in the element at index `index` in the array of `int_array`
// pre  : `int_array` follows all invariants of DynIntArray
// post :
//      - the `array_ptr` member of `int_array` will point to a valid array allocation
//        in dynamic storage with the size `int_array.size+1`.
//      - all values from the original array will be preserved, with elements before `index`
//        keeping their position and elements on or after `index` shifted forward by one space
//      - does not leak memory
//      - does not access memory out of bounds
void add(DynIntArray &int_array, int index, int value) {

    // Resize array to account for extra element
    resize_int_array(int_array, int_array.size + 1);

    // Move every element on or after index `index` forward
    // to make room for new value
    for (int i = int_array.size - 2; i >= index; i--) {
        int_array.array_ptr[i + 1] = int_array.array_ptr[i];
    }
    
    // Insert the new value
    int_array.array_ptr[index] = value;
}

// desc : prints the content of the input `int_array`
// pre  : the `array_ptr` member of `int_array` points to a valid array allocation
//        in dynamic storage, or null
// post : prints the content of the array pointed by the `array_ptr member of `int_array`,
//        in order and as a comma-separated list
void print_array(DynIntArray &int_array) {
    for (int i = 0; i < int_array.size; i++) {
        // Precede every non-first element with a comma
        if (i != 0) {
            std::cout << ',';
        }
        std::cout << int_array.array_ptr[i];
    }
    std::cout << '\n';
}
