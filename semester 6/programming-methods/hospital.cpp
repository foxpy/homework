#include <iostream>
#include <string>
#include <vector>

#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"

Hospital::Hospital(const std::string &name) {
	_name = name;
	std::clog << "Created hospital " << name << std::endl;
}

void Hospital::add_doctor(Doctor doctor) {
	doctors.push_back(doctor);
	std::clog << "Added doctor " << doctor.name() << " to hospital " << _name << std::endl;
}

void Hospital::add_patient(Patient patient) {
	patients.push_back(patient);
	std::clog << "Added patient " << patient.name() << " to hospital " << _name << std::endl;
}
