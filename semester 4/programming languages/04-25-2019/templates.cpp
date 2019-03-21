#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <cstdint>

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
void show_array(T& array, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++) {
		std::cout << i << ": " << array[i] << std::endl;
	}
}

int main()
{
	int test1[ARRAY_SIZE] = ARRAY;
	std::array<int, ARRAY_SIZE> test2 ARRAY;
	std::vector<int> test3 = ARRAY;

	std::cout << "Working on C array:" << std::endl;
	multiply_by_min(test1, 4);
	show_array(test1, 4);

	std::cout << "Working on C++ array:" << std::endl;
	multiply_by_min(test2, 4);
	show_array(test2, 4);

	std::cout << "Working on C++ vector:" << std::endl;
	multiply_by_min(test3, 4);
	show_array(test3, 4);
	return EXIT_SUCCESS;
}
