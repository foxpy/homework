#pragma once
#include <string>

class Human {
public:
	Human() = default;
	Human(const std::string &name,
	      unsigned age);
	const char* name() const;
	unsigned age() const;
	virtual void print_info() const = 0;
private:
	std::string _name;
	unsigned _age;
};
