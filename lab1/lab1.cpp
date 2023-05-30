// Bryan Kim
// lab1.cpp
// This file accepts up to 100 integer inputs from user and
// prints the minimum, maximum, and sum of all values. Inputs are
// no longer accepted after a negative value.

#include <iostream>

//disc: prints a welcome message.
//pre:  none
//post: none
void welcome();

//disc: prints a goodbye message.
//pre:  none
//post: none
void goodbye();

//disc: accepts a user's inputted integer and returns it.
//pre:  the accepted integer must be > -100 and < 100.
//      assumed input is an integer.
//post: returns integer between the aforementioned range.
int input();

//disc: finds and prints the minimum, maximum, and sum of all values in the array
//      values[].
//pre:  count must be the number of relevant elements, values[] should have <= 100 
//      elements.
//post: prints the correct values after the array has been traversed.
void print_statistics(int values[], int count);

int const MAX = 100;
int const MIN = -100;

//desc: missing
//pre : missing
//post: missing
int main() {
	int count = 0;
  	int values[MAX];
  	int current_val;
  
  	welcome();
  	while (count < MAX && current_val >= 0) {
    	current_val = input();
    	values[count] = current_val;
    	count++;
  	}
  	print_statistics(values, count);
  	goodbye();
  	return 0;
}

void welcome() {
  	std::cout << "\n\nWelcome!\n\n";
}

void goodbye() {
	std::cout << "\n\nGoodbye!\n\n";
}

int input() {
  	int input_value = MAX + 1;
  
  	//requests input until the integer is between the range.
  	while (input_value < MIN || input_value > MAX) {
    	std::cout << std::endl << "Please enter an integer (between -100 and 100): ";
    	std::cin >> input_value;
 	}
  	return input_value;
}

void print_statistics(int values[], int count) {
  	int max = MIN - 1;  
  	int min = MAX + 1;
  	int sum = 0;

  	//goes through the array and finds min, max, and adds all
  	//values together in count.
  	for (int i = 0; i < count - 1; i++) {
   		 if (values[i] > max) {
    		  max = values[i];
    	}
    
		if (values[i] < min && values[i] >= 0) {
     		 min =  values[i];
   		}
    
    	sum += values[i];
  	}
  
  	//prints values
  	std::cout << std::endl << "Minimum Value: " << min << std::endl;
  	std::cout << std::endl << "Maximum Value: " << max << std::endl;
  	std::cout << std::endl << "Sum of all Values: " << sum << std::endl;
}
