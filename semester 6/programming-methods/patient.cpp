#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "disease.hpp"
#include "patient.hpp"

Patient::Patient(const std::string &name,
                 const unsigned age) {
	this->name = name;
	this->age = age;
	std::clog << "Createt patient " << name << " " << age << " years old" << std::endl;
}

Patient::Patient(const std::string &name,
                 const unsigned age,
                 const std::vector<Disease> &diseases) {
	this->name = name;
	this->age = age;
	std::copy(diseases.cbegin(), diseases.cend(), std::back_inserter(this->diseases));
	std::clog << "Created patient " << name << " " << age << " years old";
	if (!diseases.empty()) {
		std::clog << " with several diseases:";
		for (auto i : diseases) std::clog << std::endl << '\t' << i;
	}
	std::clog << std::endl;
}
