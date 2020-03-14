#pragma once

#include <string>

class Human {
public:
	Human(const std::string &name,
	      unsigned age);
	const char* name() const;
	unsigned age() const;
private:
	std::string _name;
	unsigned _age;
};
