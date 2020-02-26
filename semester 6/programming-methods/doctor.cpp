#include <iostream>

#include "doctor.hpp"

Doctor::Doctor(const std::string &name,
               const unsigned age) {
	this->name = name;
	this->age = age;
	std::clog << "Created doctor " << name << std::endl;
}
