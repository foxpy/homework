#include <iostream>
#include <array>
#include <queue>
#include <cassert>
#include "heap.hpp"

int main() {
	std::array<int, 8> input = { 4, 2, 9, 6, 1, 8, 13, 2 };
	std::priority_queue<int> stdq;
	heap<int> myq;

	assert(stdq.empty());
	assert(myq.empty());

	stdq.push(7);
	myq.push(7);
	assert(!stdq.empty());
	assert(!myq.empty());
	assert(stdq.top() == 7);
	assert(myq.top() == 7);

	for (auto i : input) {
		stdq.push(i);
		myq.push(i);
	}

	while (!stdq.empty()) {
		std::cout << stdq.top() << ' ';
		stdq.pop();
	}
	std::cout << std::endl;
	while (!myq.empty()) {
		std::cout << myq.top() << ' ';
		myq.pop();
	}
	std::cout << std::endl;
}
