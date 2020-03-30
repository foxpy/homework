#include "human.hpp"

Human::Human(const std::string &name,
             unsigned age) {
	this->_name = name;
	this->_age = age;
}

const char* Human::name() const {
	return _name.c_str();
}

unsigned Human::age() const {
	return _age;
}
