#pragma once

#include <string>
#include <vector>

#include "doctor.hpp"
#include "patient.hpp"

class Hospital {
public:
	Hospital(const std::string &title);
	void add_doctor(Doctor &doctor);
	void add_patient(Patient &patient);
private:
	std::string _title;
	std::vector<Doctor> doctors;
	std::vector<Patient> patients;
};
