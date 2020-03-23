#pragma once

#include <string>
#include <vector>

#include "human.hpp"
#include "disease.hpp"

class Patient: public Human {
public:
	Patient(const std::string &name = "Alex",
	        unsigned age = 42);
	Patient(const std::string &name,
	        unsigned age,
	        const std::vector<Disease> &diseases);
	bool is_ill() const;
private:
	std::vector<Disease> diseases;
};
