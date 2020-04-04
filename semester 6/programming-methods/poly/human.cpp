#include "human.hpp"
#include <string>

Human::Human(const std::string &name,
             unsigned age) {
	_name = name;
	_age = age;
}

const char* Human::name() const {
	return _name.c_str();
}

unsigned Human::age() const {
	return _age;
}
