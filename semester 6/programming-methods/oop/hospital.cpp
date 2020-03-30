#include <iostream>
#include <string>
#include <stdexcept>
#include <random>

#include "config.hpp"
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

bool Hospital::run() {
	if (num_doc == 0) {
		std::cout << "There are no doctors to cure anyone... end of working day" << std::endl;
		return false;
	}
	std::cout << "Total doctors: " << num_doc << std::endl;
	if (num_pat == 0) {
		std::cout << "There are no patients to be cured... end of working day" << std::endl;
		return false;
	}
	std::cout << "Total patients: " << num_pat << std::endl;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned> dis_pat(0, num_pat-1);
	std::cout << "Picking patient at random... ";
	unsigned rand_pat = dis_pat(gen);
	std::cout << patients[rand_pat].name() << ", age: " << patients[rand_pat].age()
	          << (patients[rand_pat].is_ill() ? ", ill" : ", healthy") << std::endl;
	if (!patients[rand_pat].is_ill()) {
		discharge_patient(rand_pat);
		return true;
	}
	auto rc = patients[rand_pat].get_diseases();
	for (auto it = rc.first; it != rc.second; ++it) {
		for (std::size_t i = 0; i < num_doc; ++i) {
			if (doctors[i].can_cure(*it)) {
				patients[rand_pat].cure(*it);
			}
		}
	}

	return true;
}

void Hospital::discharge_patient(std::size_t id) {
	if (num_pat == 0)
		throw std::underflow_error("No patients to discharge");
	if (id > num_pat)
		throw std::invalid_argument("Patient out of range");
#	ifdef DEBUG_INFO
		std::clog << "Patient " << patients[id].name() << " has been discharged" << std::endl;
#	endif
	patients[id] = patients[num_pat--];
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
