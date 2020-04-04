#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "doctor.hpp"

Doctor::Doctor(const std::string &name,
               unsigned age,
               const std::vector<Disease> &cures): Human(name, age) {
	_money = 0;
	std::copy(cures.cbegin(), cures.cend(), std::back_inserter(this->cures));
}

bool Doctor::can_cure(Disease disease) const {
	return std::find(cures.cbegin(), cures.cend(), disease) != cures.cend();
}

void Doctor::pay(unsigned amount) {
	_money += amount;
}

void Doctor::charge(unsigned amount) {
	_money -= amount;
}

int Doctor::money() const {
	return _money;
}

void Doctor::print_info() const {
	std::cout << "Doctor " << name() << ", " << age() << " years old, " << money() << " currency, cures: ";
	for (auto i : cures) {
		std::cout << i << ' ';
	}
	std::cout << std::endl;
}
