#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "config.h"
#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"

Hospital::Hospital(const std::string &title,
                   std::size_t doctor_capacity,
				   std::size_t patient_capacity) {
	_title = title;
	size_doc = doctor_capacity;
	size_pat = patient_capacity;
	num_doc = num_pat = 0;
	doctors = static_cast<Doctor*> (::operator new(sizeof(Doctor) * doctor_capacity));
	patients = static_cast<Patient*> (::operator new(sizeof(Patient) * patient_capacity));
#ifdef DEBUG_INFO
	std::clog << "Created hospital " << title << " with capacity of " <<
	             doctor_capacity << " doctors and " <<
	             patient_capacity << " patients" << std::endl;
#endif
}

Hospital::~Hospital() {
	delete doctors;
	delete patients;
}

void Hospital::add_doctor(Doctor &doctor) {
	if (num_doc == size_doc)
		throw std::overflow_error("No more place for doctors");
	doctors[num_doc++] = doctor;
#ifdef DEBUG_INFO
	std::clog << "Added doctor " << doctor.name() << " to hospital " << _title << std::endl;
#endif
}

void Hospital::add_patient(Patient &patient) {
	if (num_pat == size_pat)
		throw std::overflow_error("No more place for patients");
	patients[num_pat++] = patient;
#ifdef DEBUG_INFO
	std::clog << "Added patient " << patient.name() << " to hospital " << _title << std::endl;
#endif
}

const char* Hospital::title() const {
	return _title.c_str();
}
