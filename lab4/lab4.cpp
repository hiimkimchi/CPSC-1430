// Bryan Kim
// lab4.cpp
// This file creates a new int *array and the user sets the number of elements
// and the contents of the elements. Then the array is reversed and all elements
// barring the last one is printed.

#include <iostream>

//desc: creates an array with count elements
//pre : count should be over 0
//post: array pointer should be used
int *new_int_array(int count);

//desc: deletes a created array
//pre : pointer to an int array must exist
//post: none
void delete_int_array(int *array_ptr);

//desc: reads in values and stores them in the array
//pre : must have an initialized pointer to an array and int count
//post: none
void read_ints(int *array_ptr, int count);

//desc: takes the array and reverses the elements in it
//pre : must have an initialized array_ptr and int count
//post: none
void reverse(int array_ptr[], int count);

//desc: accepts integer for size and integers for elements in array[size].
//      reverses the array without the first element.
//pre : size must be non negative
//post: the lifetime of the dynamic array must be ended once it is done being used.
int main() {
    int *array = nullptr;
    int size = -1;

    //input size of dynamic array (retry if less than 1)
    while (size < 1) {
        std::cout << "Please enter a NON NEGATIVE integer for the size of the "
                  << "array: ";
        std::cin >> size;
    }

    array = new_int_array(size);
    read_ints(array, size);
    reverse(array, size);

    //prints each element except the last
    for (int i = 0; i < size - 1; i++) {
        std::cout << *(array + i) << " ";
    }
    std::cout << std::endl << std::endl;

    delete_int_array(array);
    return 0;
}

int *new_int_array(int count) {
    int *array = new int[count];
    return array;
}

void delete_int_array(int *array_ptr) {
    delete[] array_ptr;
}

void read_ints(int *array_ptr, int count) {
    std::cout << std::endl << std::endl
              << "Input integers differentiated with a space between: ";

    //inputs each integer value seperated by white space.
    for (int i = 0; i < count; i++) {
        std::cin >> *(array_ptr + i);
    }
}

void reverse(int array_ptr[], int count) {
    int *temp_array = new_int_array(count);
    int j = 0;
    //set values in temporary array to values opposite of our array_ptr
    for (int i = count - 1; i >= 0; i--) {
        temp_array[j] = array_ptr[i];
        j++;
    }

    //set our array_ptr values to the temporary array values
    for (int i = 0; i < count; i++) {
        array_ptr[i] = temp_array[i];
    }
    delete[] temp_array;
}
