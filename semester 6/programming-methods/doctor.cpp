#include <iostream>
#include <vector>
#include <iterator>

#include "doctor.hpp"
#include "disease.hpp"

Doctor::Doctor(const std::string &name,
               const unsigned age) {
	_name = name;
	_age = age;
	std::clog << "Created doctor " << name << " " << age << " years old" << std::endl;
}

Doctor::Doctor(const std::string &name,
               const unsigned age,
               const std::vector<Disease> &cures) {
	_name = name;
	_age = age;
	std::copy(cures.cbegin(), cures.cend(), std::back_inserter(this->cures));
	std::clog << "Created doctor " << name << " " << age << " years old";
	if (!cures.empty()) {
		std::clog << " which cures several diseases:";
		for (auto i : cures) std::clog << std::endl << '\t' << i;
	}
	std::clog << std::endl;
}

const char* const Doctor::name() const {
	return _name.c_str();
}

const unsigned Doctor::age() const {
	return _age;
}
