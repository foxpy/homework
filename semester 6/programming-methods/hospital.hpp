#pragma once

#include <string>
#include <cstddef>

#include "doctor.hpp"
#include "patient.hpp"

class Hospital {
public:
	Hospital(const std::string &title,
	         std::size_t doctor_capacity = 5,
	         std::size_t patient_capacity = 10);
	Hospital(const Hospital &hospital);
	~Hospital();
	const char* title() const;
	void add_doctor(const Doctor &doctor);
	void add_patient(const Patient &patient);
	bool run();
	friend Hospital& operator<< (Hospital &hospital,
	                             const Doctor &doctor);
	friend Hospital& operator<< (Hospital &hospital,
	                             const Patient &patient);
private:
	void discharge_patient(std::size_t id);
	std::string _title;
	std::size_t size_doc, size_pat, num_doc, num_pat;
	Doctor *doctors;
	Patient *patients;
};
