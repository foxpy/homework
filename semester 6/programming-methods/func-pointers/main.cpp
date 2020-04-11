#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include "function-pointers.hpp"

void help(const char* program_name);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		help(argv[0]);
		std::exit(EXIT_FAILURE);
	}
	Filesystem fs(argv[1]);
	std::vector<Patient> patients;
	fs.read(std::back_inserter(patients));
	fs.write(patients.cbegin(), patients.cend());
}

void help(const char *program_name) {
	std::cerr << "Usage: " << program_name << " <database_file>" << std::endl;
}
