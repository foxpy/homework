#include <string>
#include <cctype>
#include "15.hpp"

std::string lab15(const std::string &str) {
	std::string ret;
	for (char c : str) {
		if (std::isdigit(c)) {
			ret.push_back(c);
		}
	}
	return ret;
}
