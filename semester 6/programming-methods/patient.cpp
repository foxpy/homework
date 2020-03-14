#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "disease.hpp"
#include "patient.hpp"

Patient::Patient(const std::string &name,
                 unsigned age): Human(name, age) {
	std::clog << "Created patient " << name << " " << age << " years old" << std::endl;
}

Patient::Patient(const std::string &name,
                 unsigned age,
                 const std::vector<Disease> &diseases): Human(name, age) {
	std::copy(diseases.cbegin(), diseases.cend(), std::back_inserter(this->diseases));
	std::clog << "Created patient " << name << " " << age << " years old";
	if (!diseases.empty()) {
		std::clog << " with several diseases:";
		for (auto i : diseases) std::clog << std::endl << '\t' << i;
	}
	std::clog << std::endl;
}

bool Patient::is_ill() const {
	return !diseases.empty();
}
