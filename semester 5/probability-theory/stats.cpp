#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>

namespace pt {
	template<class InputIt>
	double expected(InputIt first, InputIt last);
	template<class InputIt>
	double dispersion(InputIt first, InputIt last);
	double standard_deviation(double dispersion);
	template<class InputIt>
	double chosen_dispersion(InputIt first, InputIt last, double expected);
	double corrected_dispersion(double chosen_dispersion, unsigned n);
	template<class InputIt>
	std::vector<double> variation_series(InputIt first, InputIt last);
	template<class InputIt>
	std::map<double, unsigned> frequency_polygon(InputIt first, InputIt last);
	template<class InputIt>
	std::vector<double> histogram(InputIt first, InputIt last, unsigned len);
}

int main(int argc, char *argv[]) {
	std::vector<double> input;

	if (argc != 2) {
		std::clog << "Usage: " << argv[0] << " FILENAME" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::ifstream istrm(argv[1], std::ios::in);
	if (!istrm.is_open()) {
		std::cerr << "Failed to open file: " << argv[1] << std::endl;
		exit(EXIT_FAILURE);
	}
	std::copy(std::istream_iterator<double>(istrm), std::istream_iterator<double>(), std::back_inserter(input));

	double expected = pt::expected(input.begin(), input.end());
	double dispersion = pt::dispersion(input.begin(), input.end());
	double standard_deviation = pt::standard_deviation(dispersion);
	double chosen_dispersion = pt::chosen_dispersion(input.begin(), input.end(), expected);
	double corrected_dispersion = pt::corrected_dispersion(chosen_dispersion, input.size());
	double corrected_standard_deviation = pt::standard_deviation(corrected_dispersion);
	std::vector<double> variation_series = pt::variation_series(input.begin(), input.end());
	std::map<double, unsigned> frequency_polygon = pt::frequency_polygon(input.begin(), input.end());
	std::vector<double> histogram = pt::histogram(input.begin(), input.end(), 25);

	std::cout << "Input data: ";
	for (std::vector<double>::iterator i = input.begin(); i != input.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;

	std::cout << "Expected: " << expected << std::endl;
	std::cout << "Dispersion: " << dispersion << std::endl;
	std::cout << "Standard deviation: " << standard_deviation << std::endl;
	std::cout << "Chosen dispersion: " << chosen_dispersion << std::endl;
	std::cout << "Corrected dispersion: " << corrected_dispersion << std::endl;
	std::cout << "Corrected standard deviation: " << corrected_standard_deviation << std::endl;

	std::cout << "Variation series: ";
	for (std::vector<double>::iterator i = variation_series.begin(); i != variation_series.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;

	std::cout << "Frequency polygon:\t";
	for (std::map<double, unsigned>::iterator i = frequency_polygon.begin(); i != frequency_polygon.end(); ++i)
		std::cout << i-> first << '=' << i->second << '\t';
	std::cout << std::endl;

	std::cout << "Histogram: ";
	for (std::vector<double>::iterator i = histogram.begin(); i != histogram.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;
}

namespace pt {
	template<class InputIt>
	double expected(InputIt first, InputIt last) {
		return std::accumulate(first, last, static_cast<double>(0)) / (last - first);
	}

	template<class InputIt>
	double dispersion(InputIt first, InputIt last) {
		double sum = 0;
		size_t len = last - first;
		for (; first != last; ++first)
			sum += std::pow(*first, 2);
		return sum / len;
	}

	double standard_deviation(double dispersion) {
		return std::sqrt(dispersion);
	}

	template<class InputIt>
	double chosen_dispersion(InputIt first, InputIt last, double expected) {
		double sum = 0;
		size_t len = last - first;
		for (; first != last; ++first)
			sum += std::pow((*first - expected), 2);
		return sum / len;
	}

	double corrected_dispersion(double chosen_dispersion, unsigned n) {
		return static_cast<double>(n)/(n-1)*chosen_dispersion;
	}

	template<class InputIt>
	std::vector<double> variation_series(InputIt first, InputIt last) {
		std::vector<double> result;
		std::copy(first, last, std::back_inserter(result));
		std::sort(result.begin(), result.end());
		return result;
	}

	template<class InputIt>
	std::map<double, unsigned> frequency_polygon(InputIt first, InputIt last) {
		std::map<double, unsigned> result;
		for (; first != last; ++first)
			++result[*first];
		return result;
	}

	template<class InputIt>
	std::vector<double> histogram(InputIt first, InputIt last, unsigned len) {
		size_t entries = (last - first)/len;
		std::vector<double> result;
		double sum;
		for (unsigned i = 0; i < len; ++i) {
			sum = 0;
			for (InputIt j = std::next(first, i); j < last; j = std::next(j, len))
				sum += *j;
			result.push_back(sum/entries);
		}
		return result;
	}
}
