#include <string>
#include "18.hpp"

void lab18(std::string &str) {
	for (auto &c : str) {
		if (c == ':') {
			c = '.';
		}
	}
}
