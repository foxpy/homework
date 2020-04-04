#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "patient.hpp"
#include "disease.hpp"

Patient::Patient(const std::string &name,
                 unsigned age,
                 const std::vector<Disease> &diseases): Human(name, age) {
	_money = 0;
	std::copy(diseases.cbegin(), diseases.cend(), std::back_inserter(this->diseases));
}

bool Patient::is_ill() const {
	return !diseases.empty();
}

void Patient::cure_from(Disease disease) {
	for (auto it = diseases.begin(); it != diseases.end(); ) {
		if (*it == disease) {
			it = diseases.erase(it);
		} else {
			++it;
		}
	}
}

Disease Patient::needs_cure_of() const {
	return diseases.back();
}

void Patient::pay(unsigned amount) {
	_money += amount;
}

void Patient::charge(unsigned amount) {
	_money -= amount;
}

int Patient::money() const {
	return _money;
}

void Patient::print_info() const {
	std::cout << "Patient " << name() << ", " << age() << " years old, " << money() << " currency, diseases: ";
	for (auto i : diseases) {
		std::cout << i << ' ';
	}
	std::cout << std::endl;
}
