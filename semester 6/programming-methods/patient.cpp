#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "disease.hpp"
#include "patient.hpp"

Patient::Patient(const std::string &name,
                 const unsigned age) {
	_name = name;
	_age = age;
	std::clog << "Created patient " << name << " " << age << " years old" << std::endl;
}

Patient::Patient(const std::string &name,
                 const unsigned age,
                 const std::vector<Disease> &diseases) {
	_name = name;
	_age = age;
	std::copy(diseases.cbegin(), diseases.cend(), std::back_inserter(this->diseases));
	std::clog << "Created patient " << name << " " << age << " years old";
	if (!diseases.empty()) {
		std::clog << " with several diseases:";
		for (auto i : diseases) std::clog << std::endl << '\t' << i;
	}
	std::clog << std::endl;
}

const char* Patient::name() const {
	return _name.c_str();
}

unsigned Patient::age() const {
	return _age;
}

bool Patient::is_ill() const {
	return !diseases.empty();
}
