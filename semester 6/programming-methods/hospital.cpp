#include <iostream>
#include <string>

#include "hospital.hpp"

Hospital::Hospital(const std::string &name) {
	_name = name;
	std::clog << "Created hospital " << name << std::endl;
}
