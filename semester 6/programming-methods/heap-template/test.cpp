#include <iostream>
#include <array>
#include <queue>
#include "heap.hpp"

int main() {
	std::array<int, 8> input = { 4, 2, 9, 6, 1, 8, 13, 2 };
	std::priority_queue<int> stdq;
	heap<int> myq;
	for (auto i : input)
		stdq.push(i);
	while (!stdq.empty()) {
		std::cout << stdq.top() << ' ';
		stdq.pop();
	}
	std::cout << std::endl;
}
