#include <iostream>
#include <cmath>

double area_of_triangle_no_exceptions(double a, double b, double c)
{
	double s = (a+b+c) / 2;
	return std::sqrt(s * (s-a) * (s-b) * (s-c));
}

int main()
{
	std::cout << area_of_triangle_no_exceptions(3, 4, 5) << std::endl;
	return EXIT_SUCCESS;
}
