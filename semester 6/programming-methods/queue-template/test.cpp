#include <iostream>
#include <array>
#include <queue>
#include <cassert>
#include "queue.hpp"

void test_int() {
	std::array<int, 8> input = { 4, 2, 9, 6, 1, 8, 13, 2 };
	std::queue<int> stdq;
	heap<int> myq;

	assert(stdq.empty());
	assert(myq.empty());

	stdq.push(7);
	myq.push(7);
	assert(!stdq.empty());
	assert(!myq.empty());
	assert(stdq.front() == 7);
	assert(myq.front() == 7);

	for (auto i : input) {
		stdq.push(i);
		myq.push(i);
	}

	assert(stdq.size() == 9);
	assert(myq.size() == 9);

	while (!stdq.empty()) {
		std::cout << stdq.front() << ' ';
		stdq.pop();
	}
	std::cout << std::endl;
	while (!myq.empty()) {
		std::cout << myq.front() << ' ';
		myq.pop();
	}
	std::cout << std::endl;
}

void test_char() {
	std::array<char, 8> input = { 'a', 's', 'q', '0', '1', '8', 'p', 'c' };
	std::queue<char> stdq;
	heap<char> myq;

	assert(stdq.empty());
	assert(myq.empty());

	stdq.push('x');
	myq.push('x');
	assert(!stdq.empty());
	assert(!myq.empty());
	assert(stdq.front() == 'x');
	assert(myq.front() == 'x');

	for (auto i : input) {
		stdq.push(i);
		myq.push(i);
	}

	assert(stdq.size() == 9);
	assert(myq.size() == 9);

	while (!stdq.empty()) {
		std::cout << stdq.front() << ' ';
		stdq.pop();
	}
	std::cout << std::endl;
	while (!myq.empty()) {
		std::cout << myq.front() << ' ';
		myq.pop();
	}
	std::cout << std::endl;
}

void test_float() {
	std::array<float, 8> input = { 4.6, 7.5, 1.0, -0.4, 19.6, 83762.3093, -62.4, 0.01 };
	std::queue<float> stdq;
	heap<float> myq;

	assert(stdq.empty());
	assert(myq.empty());

	stdq.push(3.0);
	myq.push(3.0);
	assert(!stdq.empty());
	assert(!myq.empty());
	assert(stdq.front() == 3.0);
	assert(myq.front() == 3.0);

	for (auto i : input) {
		stdq.push(i);
		myq.push(i);
	}

	assert(stdq.size() == 9);
	assert(myq.size() == 9);

	while (!stdq.empty()) {
		std::cout << stdq.front() << ' ';
		stdq.pop();
	}
	std::cout << std::endl;
	while (!myq.empty()) {
		std::cout << myq.front() << ' ';
		myq.pop();
	}
	std::cout << std::endl;
}

int main() {
	test_int();
	test_char();
	test_float();
}
