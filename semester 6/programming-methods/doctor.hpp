#pragma once

#include <string>
#include <vector>

#include "disease.hpp"

class Doctor {
private:
	std::string name;
	unsigned age;
	std::vector<Disease> cures;
public:
	Doctor(const std::string &name,
	       const unsigned age);
	Doctor(const std::string &name,
	       const unsigned age,
	       const std::vector<Disease> &cures);
};
