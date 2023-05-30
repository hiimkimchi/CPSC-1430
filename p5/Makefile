flags =  -Wall -pedantic -std=c++11

p5 : stack.o queue.o p5.cpp
	g++ p5.cpp queue.o stack.o   $(flags) -Werror -g -o p5

queue.o : queue.h queue.cpp
	g++ queue.cpp                $(flags) -Werror -g -c

stack.o : stack.h stack.cpp
	g++ stack.cpp                $(flags) -Werror -g -c
