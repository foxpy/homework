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

int main() {
	Stack<double> stack;

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

	return EXIT_SUCCESS;
}
