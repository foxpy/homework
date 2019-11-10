#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>
#include <mgl2/mgl.h>

namespace pt {
	template<class InputIt>
	double expected(InputIt first, InputIt last);
	template<class InputIt>
	double dispersion(InputIt first, InputIt last);
	double standard_deviation(double dispersion);
	template<class InputIt>
	double chosen_dispersion(InputIt first, InputIt last, double expected);
	double corrected_dispersion(double chosen_dispersion, std::size_t n);
	template<class InputIt>
	std::vector<double> variation_series(InputIt first, InputIt last);
	template<class InputIt>
	std::map<double, unsigned> frequency_polygon(InputIt first, InputIt last);
	template<class InputIt>
	std::vector<double> histogram(InputIt first, InputIt last, std::size_t len);
}

namespace plt {
	void frequency_polygon(std::map<double, unsigned> &src, std::string filename);
	void histogram(std::vector<double> &src, std::string filename);
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
	for (std::vector<double>::iterator it = input.begin(); it != input.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	std::cout << "Expected: " << expected << std::endl;
	std::cout << "Dispersion: " << dispersion << std::endl;
	std::cout << "Standard deviation: " << standard_deviation << std::endl;
	std::cout << "Chosen dispersion: " << chosen_dispersion << std::endl;
	std::cout << "Corrected dispersion: " << corrected_dispersion << std::endl;
	std::cout << "Corrected standard deviation: " << corrected_standard_deviation << std::endl;

	std::cout << "Variation series: ";
	for (std::vector<double>::iterator it = variation_series.begin(); it != variation_series.end(); ++it)
		std::cout << *it << ' ';
	std::cout << std::endl;

	plt::histogram(histogram, "histogram.png");
	std::cout << "Histogram saved in histogram.png" << std::endl;
	plt::frequency_polygon(frequency_polygon, "frequency_polygon.png");
	std::cout << "Frequency polygon saved in frequency_polygon.png" << std::endl;
}

namespace pt {
	template<class InputIt>
	double expected(InputIt first, InputIt last) {
		return std::accumulate(first, last, static_cast<double>(0)) / (std::distance(first, last));
	}

	template<class InputIt>
	double dispersion(InputIt first, InputIt last) {
		double sum = 0;
		std::size_t len = static_cast<std::size_t>(std::distance(first, last));
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
		std::size_t len = static_cast<std::size_t>(std::distance(first, last));
		for (; first != last; ++first)
			sum += std::pow((*first - expected), 2);
		return sum / len;
	}

	double corrected_dispersion(double chosen_dispersion, std::size_t n) {
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
	std::vector<double> histogram(InputIt first, InputIt last, std::size_t len) {
		std::size_t entries = static_cast<std::size_t>(std::distance(first, last))/len;
		std::vector<double> result;
		double sum;
		for (unsigned i = 0; i < len; ++i) {
			sum = 0;
			for (InputIt j = std::next(first, i); j < last; std::advance(j, len))
				sum += *j;
			result.push_back(sum/entries);
		}
		return result;
	}
}

namespace plt {
	void frequency_polygon(std::map<double, unsigned> &src, std::string filename) {
		mglGraph gr;
		mglData data(static_cast<long>(src.size()), 1);
		for (std::map<double, unsigned>::iterator it = src.begin(); it != src.end(); ++it)
			data[std::distance(src.begin(), it)] = it->second;
		unsigned max = std::max_element(src.begin(), src.end(),
		               [](std::pair<double, unsigned> a, std::pair<double, unsigned> b) {
			return a.second < b.second;
		})->second;
		gr.SetRanges(0, 1, 0, max+(1+max/10));
		gr.Box();
		gr.Axis("y");
		gr.Plot(data);
		gr.WriteFrame(filename.c_str());
	}

	void histogram(std::vector<double> &src, std::string filename) {
		mglGraph gr;
		mglData data(static_cast<long>(src.size()), 1);
		for (std::vector<double>::iterator it = src.begin(); it != src.end(); ++it)
			data[it-src.begin()] = *it;
		double max = *std::max_element(src.begin(), src.end());
		gr.SetRanges(0, 1, 0, 1.1*max);
		gr.Box();
		gr.Axis("y");
		gr.Bars(data);
		gr.WriteFrame(filename.c_str());
	}
}
