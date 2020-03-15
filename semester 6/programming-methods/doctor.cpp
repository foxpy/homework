#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "config.h"
#include "doctor.hpp"
#include "disease.hpp"

Doctor::Doctor(const std::string &name,
               unsigned age): Human(name, age) {
#ifdef DEBUG_INFO
	std::clog << "Created doctor " << name << " " << age << " years old" << std::endl;
#endif
}

Doctor::Doctor(const std::string &name,
               unsigned age,
               const std::vector<Disease> &cures): Human(name, age) {
	std::copy(cures.cbegin(), cures.cend(), std::back_inserter(this->cures));
#ifdef DEBUG_INFO
	std::clog << "Created doctor " << name << " " << age << " years old";
	if (!cures.empty()) {
		std::clog << " which cures several diseases:";
		for (auto i : cures) std::clog << std::endl << '\t' << i;
	}
	std::clog << std::endl;
#endif
}

bool Doctor::can_cure(Disease disease) const {
	return std::find(cures.cbegin(), cures.cend(), disease) != cures.cend();
}
