#include <vector>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include "function-pointers.hpp"

Tui::Tui(std::vector<Patient> *patients) {
	this->patients = patients;
	menu_items[0] = Menu { 1, "Add patient", &add_patient };
	menu_items[1] = Menu { 2, "Delete patient", &delete_patient };
	menu_items[2] = Menu { 3, "Find patient", &find_patient };
	menu_items[3] = Menu { 4, "Show patient", &show_patient };
}

void Tui::run() {
	clear_screen();
	print_menu();
	std::size_t cmd;
	bool exit = false;
	while (!exit) {
		if (std::cin.eof()) break;
		std::cout << ">>> ";
		std::cin >> cmd;
		clear_screen();
		if (cmd == 5)
			exit = true;
		else if (cmd > 0 && cmd < 5)
			menu_items[cmd-1].function(patients);
		std::cout << std::endl;
		print_menu();
	}
	clear_screen();
}

void Tui::print_menu() {
	for (auto i: menu_items) {
		std::cout << i.number << '\t' << i.command << std::endl;
	}
	std::cout << 5 << '\t' << "Exit" << std::endl;
}

void Tui::clear_screen() {
	std::cout << "\x1B[2J\x1B[H";
	std::cout.flush();
}

void add_patient(std::vector<Patient> *patients) {
	Patient patient;
	std::cout << ">>> Name: ";
	std::cin >> patient.name;
	std::cout << ">>> Age: ";
	std::cin >> patient.age;
	std::cout << ">>> Disease: ";
	std::cin >> patient.disease;
	std::string severity;
	std::cout << ">>> Severity: ";
	std::cin >> severity;
	std::transform(severity.begin(), severity.end(), severity.begin(), [](unsigned char c) {
		return std::tolower(c);
	});
	if (severity == "low")
		patient.severity = LowSeverity;
	else if (severity == "medium")
		patient.severity = MediumSeverity;
	else if (severity == "high")
		patient.severity = HighSeverity;
	else
		patient.severity = ExtremeSeverity;
	patients->push_back(patient);
}

void delete_patient(std::vector<Patient> *patients) {
	std::size_t num;
start:
	std::cout << "There are " << patients->size() << " patients" << std::endl;
	std::cout << ">>> ";
	std::cin >> num;
	if (num == 0 || num > patients->size()) {
		goto start;
	} else {
		patients->erase(patients->begin()+num-1);
	}
}

// TODO
void find_patient(std::vector<Patient> *patients) {
	std::cout << "HAHA TOO LAZY" << std::endl;
}

void show_patient(std::vector<Patient> *patients) {
	std::size_t num;
start:
	std::cout << "There are " << patients->size() << " patients" << std::endl;
	std::cout << ">>> ";
	std::cin >> num;
	if (num == 0 || num > patients->size()) {
		goto start;
	} else {
		print_patient((*patients)[num-1]);
	}
}

void print_patient(Patient &patient) {
	std::cout << patient.name << std::endl;
	std::cout << patient.age << " years" << std::endl;
	std::cout << "Disease: " << patient.disease << std::endl;
	std::cout << patient.severity << std::endl;
}
