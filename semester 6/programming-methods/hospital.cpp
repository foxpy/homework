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
#	ifdef DEBUG_INFO
		std::clog << "Created hospital " << title << " with capacity of " <<
		             doctor_capacity << " doctors and " <<
		             patient_capacity << " patients" << std::endl;
#	endif
}

Hospital::Hospital(const Hospital &hospital) {
	_title = hospital._title;
	_title.append(" (copy)");
	size_doc = hospital.size_doc;
	size_pat = hospital.size_pat;
	num_doc = hospital.num_doc;
	num_pat = hospital.num_pat;
	doctors = static_cast<Doctor*> (::operator new(sizeof(Doctor) * size_doc));
	patients = static_cast<Patient*> (::operator new(sizeof(Patient) * size_pat));
	for (std::size_t i = 0; i < num_doc; ++i)
		doctors[i] = hospital.doctors[i];
	for (std::size_t i = 0; i < num_pat; ++i)
		patients[i] = hospital.patients[i];
#	ifdef DEBUG_INFO
		std::clog << "Copied hospital " << hospital._title << " to " << _title << std::endl;
#	endif
}

Hospital::~Hospital() {
	delete doctors;
	delete patients;
}

const char* Hospital::title() const {
	return _title.c_str();
}

void Hospital::add_doctor(const Doctor &doctor) {
	if (num_doc == size_doc)
		throw std::overflow_error("No more place for doctors");
	doctors[num_doc++] = doctor;
#	ifdef DEBUG_INFO
		std::clog << "Added doctor " << doctor.name() << " to hospital " << _title << std::endl;
#	endif
}

void Hospital::add_patient(const Patient &patient) {
	if (num_pat == size_pat)
		throw std::overflow_error("No more place for patients");
	patients[num_pat++] = patient;
#	ifdef DEBUG_INFO
		std::clog << "Added patient " << patient.name() << " to hospital " << _title << std::endl;
#	endif
}

Hospital& operator<< (Hospital &hospital,
                      const Doctor &doctor) {
	hospital.add_doctor(doctor);
	return hospital;
}

Hospital& operator<< (Hospital &hospital,
                      const Patient &patient) {
	hospital.add_patient(patient);
	return hospital;
}
