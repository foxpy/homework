#include <iostream>
#include <array>
#include <vector>
#include <cstdlib>
#include <cstdint>

#include "templates.hpp"

template<class T>
void multiply_by_min(T& array, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++) {
		array[i] *= i;
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
	int test1[4] = {1, 2, 3, 4};
	std::array<int, 4> test2 {1, 2, 3, 4};
	std::vector<int> test3 = {1, 2, 3, 4};

	multiply_by_min(test1, 4);
	show_array(test1, 4);

	multiply_by_min(test2, 4);
	show_array(test2, 4);

	multiply_by_min(test3, 4);
	show_array(test3, 4);
	return EXIT_SUCCESS;
}
