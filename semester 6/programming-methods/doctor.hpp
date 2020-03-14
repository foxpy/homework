#pragma once

#include <string>
#include <vector>

#include "human.hpp"
#include "disease.hpp"

class Doctor: public Human {
public:
	Doctor(const std::string &name,
	       unsigned age);
	Doctor(const std::string &name,
	       unsigned age,
	       const std::vector<Disease> &cures);
	bool can_cure(Disease disease) const;
private:
	std::vector<Disease> cures;
};
