#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <string>

#include "templates.hpp"

#define ARRAY {2, -4, 0, 8}
#define ARRAY_SIZE 4

template<class T>
void multiply_by_min(T& array, size_t len)
{
	long long min = array[0];
	// how do I get the type of array passed?
	// long long is good, but it may be slower on some systems
	// e. g. on i386 or armv7h
	size_t i;
	for (i = 0; i < len; i++) {
		if (array[i] < min) min = array[i];
	}
	for (i = 0; i < len; i++) {
		array[i] *= min;
	}
}

template<class T>
void replace_zeros_by_average(T& array, size_t len)
{
	long long average = 0;
	// absolutely the same question as in line 16...
	size_t i;
	for (i = 0; i < len; i++) average += array[i];
	average /= len;
	for (i = 0; i < len; i++) {
		if (array[i] == 0) array[i] = average;
	}
}

template<class T>
void show_array(T& array, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++) {
		std::cout << i << ": " << array[i] << "\t";
	}
	std::cout << std::endl;
}

template<class T>
void Stack<T>::push(T const& element)
{
	stack.push_back(element);
}

template<class T>
T Stack<T>::pop()
{
	auto back = stack.end();
	back--;
	if (stack.empty()) {
		throw std::out_of_range("empty stack");
	} else {
		stack.pop_back();
		return *back;
	}
}

int main()
{
	int array1[ARRAY_SIZE] = ARRAY;
	std::array<int, ARRAY_SIZE> array2 ARRAY;
	std::vector<int> array3 = ARRAY;

	Stack<size_t> stack1;
	Stack<double> stack2;
	Stack<std::string> stack3;

	std::cout << "Task 1: function templates" << std::endl;

	std::cout << "Working on C array:" << std::endl;
	show_array(array1, ARRAY_SIZE);
	multiply_by_min(array1, ARRAY_SIZE);
	show_array(array1, ARRAY_SIZE);
	replace_zeros_by_average(array1, ARRAY_SIZE);
	show_array(array1, ARRAY_SIZE);

	std::cout << "Working on C++ array:" << std::endl;
	show_array(array2, ARRAY_SIZE);
	multiply_by_min(array2, ARRAY_SIZE);
	show_array(array2, ARRAY_SIZE);
	replace_zeros_by_average(array2, ARRAY_SIZE);
	show_array(array2, ARRAY_SIZE);


	std::cout << "Working on C++ vector:" << std::endl;
	show_array(array3, ARRAY_SIZE);
	multiply_by_min(array3, ARRAY_SIZE);
	show_array(array3, ARRAY_SIZE);
	replace_zeros_by_average(array3, ARRAY_SIZE);
	show_array(array3, ARRAY_SIZE);

	std::cout << std::endl << "Task 2: class templates" << std::endl;

	std::cout << "Working on stack of machine size values:" << std::endl;
	stack1.push(0xFF << 16);
	stack1.push(0b00001100 >> 2);
	stack1.pop();
	std::cout << stack1.pop() << std::endl;

	std::cout << "Working on stack of"
		" double-precision floating-point numbers:" << std::endl;
	stack2.push(12.33 * 0.004);
	stack2.push(133.0/12.1);
	stack2.pop();
	std::cout << stack2.pop() << std::endl;

	std::cout << "Working on stack of strings:" << std::endl;
	stack3.push("I am a cookie.");
	stack3.push("I am not a cookie.");
	stack3.pop();
	std::cout << stack3.pop() << std::endl;

	return EXIT_SUCCESS;
}
