#pragma once
#include <string>
#include <vector>
#include <random>
#include "doctor.hpp"
#include "patient.hpp"

class Hospital {
public:
	Hospital(const Hospital&) = delete;
	Hospital(const std::string &name);
	const char* name() const;
	void add(const Patient &patient);
	void add(const Doctor &doctor);
	void run();
	friend Hospital& operator<< (Hospital &hospital,
	                             const Patient &patient);
	friend Hospital& operator<< (Hospital &hospital,
	                             const Doctor &doctor);
private:
	void surcharge(Wallet &wallet);
	template<class Iter>
	void collect_taxes(Iter begin, Iter end) {
		while(begin != end) {
			surcharge(*begin);
			++begin;
		}
	}
	void list_stuff() const;
	std::string _name;
	std::vector<Doctor> doctors;
	std::vector<Patient> patients;
};
