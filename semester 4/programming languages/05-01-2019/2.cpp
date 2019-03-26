#include <iostream>
#include <stdexcept>

#include "2.hpp"

template<class T>
void Stack<T>::push(T const& element)
{
	if (++sp > STACK_SIZE) {
		--sp;
		throw std::overflow_error("stack overflow");
	}
	stack[sp] = element;
}

template<class T>
T Stack<T>::pop() {
	if (sp == 0) {
		throw std::overflow_error("stack underflow");
	}
	return stack[sp--];
}

template<class T>
void MyStack<T>::push(T const& element)
{
	if (++sp > STACK_SIZE) {
		--sp;
		throw stack_overflow();
	}
	stack[sp] = element;
}

template<class T>
T MyStack<T>::pop() {
	if (sp == 0) {
		throw stack_overflow();
	}
	return stack[sp--];
}

int main() {
	Stack<double> stack;
	MyStack<double> my_stack;


	std::cout << "Stack implementation with standard exceptions:" << std::endl;

	stack.push(2.4);
	stack.push(12.4);
	stack.pop();
	std::cout << stack.pop() << std::endl;
	try {
		std::cout << "Let's see if we actually can pop under stack..." << std::endl;;
		stack.pop();
		std::cout << "Looks like we can!" << std::endl;
	}
	catch (std::overflow_error& e) {
		std::cout << "No.. We cannot." << std::endl;
	}


	std::cout << std::endl << "Stack implementation with custom exceptions:" << std::endl;

	my_stack.push(2.4);
	my_stack.push(12.4);
	my_stack.pop();
	std::cout << my_stack.pop() << std::endl;
	try {
		std::cout << "Let's see if we actually can pop under stack..." << std::endl;;
		my_stack.pop();
		std::cout << "Looks like we can!" << std::endl;
	}
	catch (stack_overflow& e) {
		std::cout << "No.. We cannot." << std::endl;
	}

	return EXIT_SUCCESS;
}
