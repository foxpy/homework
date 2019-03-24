#include <iostream>
#include <cmath>
#include <stdexcept>

#define GOOD_TRIANGLE 3, 4, 5
#define BAD_TRIANGLE 10, 4, 2

double area_of_triangle_no_exceptions(double a, double b, double c)
{
	double s = (a+b+c) / 2;
	return std::sqrt(s * (s-a) * (s-b) * (s-c));
}

double area_of_triangle_exceptions(double a, double b, double c)
{
	double s = (a+b+c) / 2;
	double result = std::sqrt(s * (s-a) * (s-b) * (s-c));
	if (std::isnan(result)) {
		throw std::invalid_argument("invalid triangle");
	}
	return result;
}

int main()
{
	std::cout << "No exceptions:" << std::endl;
	std::cout << area_of_triangle_no_exceptions(GOOD_TRIANGLE) << std::endl;
	std::cout << area_of_triangle_no_exceptions(BAD_TRIANGLE) << std::endl;

	std::cout << std::endl << "Exceptions:" << std::endl;
	try {
		std::cout << area_of_triangle_exceptions(GOOD_TRIANGLE) << std::endl;
	}
	catch (std::invalid_argument) {}
	try {
		std::cout << area_of_triangle_exceptions(BAD_TRIANGLE) << std::endl;
	}
	catch (std::invalid_argument) {}

	return EXIT_SUCCESS;
}
