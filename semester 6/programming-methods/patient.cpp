#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "config.h"
#include "disease.hpp"
#include "patient.hpp"
#include "wallet.hpp"

Patient::Patient(const std::string &name,
                 unsigned age): Human(name, age) {
	money = 0;
#	ifdef DEBUG_INFO
		std::clog << "Created patient " << name << " " << age << " years old" << std::endl;
#	endif
}

Patient::Patient(const std::string &name,
                 unsigned age,
                 const std::vector<Disease> &diseases): Human(name, age) {
	money = 0;
	std::copy(diseases.cbegin(), diseases.cend(), std::back_inserter(this->diseases));
#	ifdef DEBUG_INFO
		std::clog << "Created patient " << name << " " << age << " years old";
		if (!diseases.empty()) {
			std::clog << " with several diseases:";
			for (auto i : diseases) std::clog << std::endl << '\t' << i;
		}
		std::clog << std::endl;
#	endif
}

bool Patient::is_ill() const {
	return !diseases.empty();
}

void Patient::pay(unsigned amount) {
	money += amount;
#	ifdef DEBUG_INFO
		std::clog << "Patient " << name() << " has received a compensation of " << amount <<
		             " of currency (now he has " << money << ')' << std::endl;
#	endif
}

void Patient::charge(unsigned amount) {
	money -= amount;
#	ifdef DEBUG_INFO
		std::clog << "Patient " << name() << " has been charged with " << amount <<
		             " of currency (now he has " << money << ')' << std::endl;
#	endif
}
