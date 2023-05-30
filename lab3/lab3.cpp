// Bryan Kim
// lab3.cpp
// This file takes an array of unsigned integers and sorts them
// in terms of even, threeven(divisible by 3), and other arrays

#include <iostream>
#include <fstream>

int const MAX_LENGTH = 30;
std::string const FILE_NAME = "numbers.txt";

//desc: checks if the int parameter is even
//pre : parameter must be unsigned
//post: none
bool is_even(unsigned int value);

//desc: checks if the int parameter is divisible by 3
//pre : parameter must be unsigned
//post: none
bool is_threeven(unsigned int value);

//desc: prints the array provided in the parameters until relevent elements
//pre : array must have less than or equal to 30 elements
//post: none
void print_list(unsigned int list[], unsigned int count);

int main() {
    unsigned int even_list[MAX_LENGTH];
    unsigned int threeven_list[MAX_LENGTH];
    unsigned int other_list[MAX_LENGTH];
    unsigned int even_count = 0;
    unsigned int threeven_count = 0;
    unsigned int other_count = 0;
    bool is_num_even;
    bool is_num_threeven;
    unsigned int num;

    //check if the read in file is valid
    std::ifstream in_file;
    in_file.open(FILE_NAME);
    if(in_file.fail()) {
        std::cout << "File error, please run the program again.";
        return 0;
    }

    //read in from file and input values in the correct arrays
    while (in_file >> num) {
        is_num_even = is_even(num);
        is_num_threeven = is_threeven(num);
        if(is_num_even) {
            even_list[even_count] = num;
            even_count++;
        } else if (is_num_threeven) {
            threeven_list[threeven_count] = num;
            threeven_count++;
        } else {
            other_list[other_count] = num;
            other_count++;
        }
    }
    in_file.close();
    
    //print lists in order
    std::cout << std::endl << std::endl;
    std::cout << "Even numbers:";
    print_list(even_list, even_count);
    std::cout << "Threeven numbers:";
    print_list(threeven_list, threeven_count);
    std::cout << "The rest of the numbers:";
    print_list(other_list, other_count);

    return 0;
}

bool is_even(unsigned int value) {
    return value % 2 == 0;
}

bool is_threeven(unsigned int value) {
    return value % 3 == 0;
}

void print_list(unsigned int list[], unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        std::cout << list[i] << std::endl;
    }
    std::cout << std::endl << std::endl;
}