#include <iostream>
#include <complex>
#include <cmath>

#define FORMAT_COMPLEX(complex_num) std::real(complex_num)\
	<< (std::imag(complex_num) > 0 ? "+" : "")\
	<< (std::imag(complex_num) != 0 ? std::to_string(std::imag(complex_num)) : "")\
	<< (std::imag(complex_num) != 0 ? "i" : "")\

int main()
{
	double A, B, C, D;
	std::cout << "Enter A, B and C: " << std::endl;
	std::cin >> A >> B >> C;

	D = std::pow(B, 2) - 4*A*C;
	std::cout << "Answers: " << std::endl;

	std::complex<double> x1 = (-B + std::sqrt(std::complex<double>(D, 0))) / (2 * A);
	std::complex<double> x2 = (-B - std::sqrt(std::complex<double>(D, 0))) / (2 * A);
	std::cout << "x1: " << FORMAT_COMPLEX(x1) << "," << std::endl;
	std::cout << "x2: " << FORMAT_COMPLEX(x2) << "." << std::endl;

	return EXIT_SUCCESS;
}
