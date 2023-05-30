// Bryan Kim
// lab6.cpp
// This file takes a fixed version of lab5 and converts the DynIntArray struct 
// into a class.

#include <iostream>

int const FOUR = 4;
int const FIVE = 5;

// desc : represents a dynamically allocated array of integers stored alongside
//        a count of how many elements it has
// invariants:
//      - `array_ptr` is always either null or pointing to a valid array allocation
//        in dynamic storage
//      - `size` is always set to the number of elements in the array pointed by
//        `array_ptr`
class DynIntArray {
    private:
    //fields
    int *array_ptr;
    int  size;

    public:
    //constructors
    DynIntArray(int count);
    DynIntArray(DynIntArray const &other);

    //methods
    void print();
    void resize(int new_size);
    int remove(int index);
    void add(int index, int value);

    //destructor
    ~DynIntArray();
};

// desc : returns a new DynIntArray with the corresponding size
// pre  : `size` is not negative
// post :
//      - the `array_ptr` member of the returned value points to a newly allocated int
//        array in dynamic storage with `size` elements
//      - the `size` member of the returned value matches the input `size` value
//      - does not leak memory
//      - does not access memory out of bounds
DynIntArray::DynIntArray(int count) {
    array_ptr = new int[count];
    size      = count;
}

// desc : returns a copy of the supplied DynIntArray instance
// pre  : `other` follows all invariants of DynIntArray
// post :
//      - the array pointed by the `array_ptr` member of the return value will be an
//        independent copy of the array pointed by `other.array_ptr`, stored in
//        dynamic memory and with the same size as `other.size`
//      - does not leak memory
//      - does not access memory out of bounds
DynIntArray::DynIntArray(DynIntArray const &other) {
    size      = other.size;
    array_ptr = new int[other.size];
    for(int i = 0; i < size; i++) {
        array_ptr[i] = other.array_ptr[i];
    }
}

// desc : prints the content of the input `int_array`
// pre  : the `array_ptr` member of `int_array` points to a valid array allocation
//        in dynamic storage, or null
// post : prints the content of the array pointed by the `array_ptr member of `int_array`,
//        in order and as a comma-separated list
void DynIntArray::print() {
    for (int i = 0; i < size; i++) {
            if (i != 0) {
                std::cout << ',';
            }
            std::cout << array_ptr[i];
    }
    std::cout << '\n';
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
void DynIntArray::resize(int new_size) {
    // Allocate a new array
    int *new_array_ptr = new int[new_size];
    int limit = (new_size < size) ? new_size : size;
    // Copy over values from old array to new array
    for (int i = 0; i < limit; i++) {
        new_array_ptr[i] = array_ptr[i];
    }
    delete[] array_ptr;
    array_ptr = new_array_ptr;
    size      = new_size;
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
int DynIntArray::remove(int index) {
    // Save the removed value, before its element is overwritten
    int removed = array_ptr[index];
    // Move every element after index `index` back by one space
    for (int i = index; i < (size - 1); i++) {
        array_ptr[i] = array_ptr[i+1];
    }
    // Resize to remove extra element at the end
    resize(size - 1);
    // Return the removed value
    return removed;
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
void DynIntArray::add(int index, int value) {
    // Resize array to account for extra element
    resize(size + 1);
    // Move every element on or after index `index` forward
    // to make room for new value
    for (int i = size-2; i >= index; i--) {
        array_ptr[i + 1] = array_ptr[i];
    }
    // Insert the new value
    array_ptr[index] = value;
}

// desc : deletes the array used by the input `int_array` to store its values
// pre  : `int_array` follows all invariants of DynIntArray
// post :
//      - as stated in the description, deletes the array pointed by the `array_ptr`
//        member of `int_array`, and sets the member to null
//      - sets the `size` of `array_ptr` to zero
//      - does not leak memory
//      - does not access memory out of bounds
DynIntArray::~DynIntArray() {
    delete[] array_ptr;
    array_ptr = nullptr;
    size      = 0;
}

// Feel free to unit test your refactored functions here
int main() {
    int removedval = 0;
    DynIntArray dyn_arr(0);
    DynIntArray second_dyn_arr(dyn_arr);
    second_dyn_arr.add(0, 1);
    second_dyn_arr.add(1, 2);
    second_dyn_arr.add(2, 3);
    removedval = second_dyn_arr.remove(1);
    second_dyn_arr.add(1, removedval);
    second_dyn_arr.print();
    return 0;
}