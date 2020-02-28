#pragma once

#include <string>
#include <vector>

#include "disease.hpp"

class Doctor {
private:
	std::string _name;
	unsigned _age;
	std::vector<Disease> cures;
public:
	Doctor(const std::string &name,
	       const unsigned age);
	Doctor(const std::string &name,
	       const unsigned age,
	       const std::vector<Disease> &cures);
	const char* const name() const;
	const unsigned age() const;
};
