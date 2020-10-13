#include <cstddef>
#include "4.hpp"

static double factorial(std::size_t n) {
	double sum = 1;
	for (std::size_t i = 1; i <= n; ++i) {
		sum *= i;
	}
	return sum;
}

double C(std::size_t n, std::size_t k) {
	return factorial(n)/(factorial(k) * factorial(n - k));
}
