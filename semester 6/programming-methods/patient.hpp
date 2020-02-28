#pragma once

#include <string>
#include <vector>

#include "disease.hpp"

class Patient {
private:
	std::string _name;
	unsigned _age;
	std::vector<Disease> diseases;
public:
	Patient(const std::string &name,
	        const unsigned age);
	Patient(const std::string &name,
	        const unsigned age,
	        const std::vector<Disease> &diseases);
	const char* name() const;
	unsigned age() const;
};
