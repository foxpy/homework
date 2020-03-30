#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>

#include "config.hpp"
#include "doctor.hpp"
#include "disease.hpp"
#include "wallet.hpp"

Doctor::Doctor(const std::string &name,
               unsigned age): Human(name, age) {
	_money = 0;
#	ifdef DEBUG_INFO
		std::clog << "Created doctor " << name << " " << age << " years old" << std::endl;
#	endif
}

Doctor::Doctor(const std::string &name,
               unsigned age,
               const std::vector<Disease> &cures): Human(name, age) {
	_money = 0;
	std::copy(cures.cbegin(), cures.cend(), std::back_inserter(this->cures));
#	ifdef DEBUG_INFO
		std::clog << "Created doctor " << name << " " << age << " years old";
		if (!cures.empty()) {
			std::clog << " which cures several diseases:";
			for (auto i : cures) std::clog << std::endl << '\t' << i;
		}
		std::clog << std::endl;
#	endif
}

Doctor::Doctor(const Patient &patient): Human(patient.name(), patient.age()) {
	_money = patient.money();
	auto rc = patient.get_diseases();
	std::copy(rc.first, rc.second, std::back_inserter(cures));

#	ifdef DEBUG_INFO
		std::clog << "Mutated patient " << patient.name() << " to doctor" << std::endl;
#	endif
}

bool Doctor::can_cure(Disease disease) const {
	return std::find(cures.cbegin(), cures.cend(), disease) != cures.cend();
}

void Doctor::pay(unsigned amount) {
	_money += amount;
#	ifdef DEBUG_INFO
		std::clog << "Doctor " << name() << " has been payed with " << amount <<
		             " of currency (now he has " << _money << ')' << std::endl;
#	endif
}

void Doctor::charge(unsigned amount) {
	_money -= amount;
#	ifdef DEBUG_INFO
		std::clog << "Doctor " << name() << " has been fined with " << amount <<
		             " of currency (now he has " << _money << ')' << std::endl;
#	endif
}

int Doctor::money() const {
	return _money;
}
