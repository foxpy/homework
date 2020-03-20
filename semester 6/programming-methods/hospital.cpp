#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"

Hospital::Hospital(const std::string &name) {
	_name = name;
#ifdef DEBUG_INFO
	std::clog << "Created hospital " << name << std::endl;
#endif
}

void Hospital::add_doctor(Doctor &doctor) {
	doctors.push_back(doctor);
#ifdef DEBUG_INFO
	std::clog << "Added doctor " << doctor.name() << " to hospital " << _name << std::endl;
#endif
}

void Hospital::add_patient(Patient &patient) {
	patients.push_back(patient);
#ifdef DEBUG_INFO
	std::clog << "Added patient " << patient.name() << " to hospital " << _name << std::endl;
#endif
}