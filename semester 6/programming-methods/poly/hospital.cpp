#include <iostream>
#include <random>
#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"
#include "wallet.hpp"

Hospital::Hospital(const std::string &name) {
	_name = name;
}

const char* Hospital::name() const {
	return _name.c_str();
}

void Hospital::add(const Patient &patient) {
	patients.push_back(patient);
}

void Hospital::add(const Doctor &doctor) {
	doctors.push_back(doctor);
}

void Hospital::run() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(25, 30);
	std::cout << "Started hospital " << name() << std::endl;
	list_stuff();
	std::cout << "Executing curing process" << std::endl;
	for (auto patient = patients.begin(); patient != patients.end(); ++patient) {
		while(patient->is_ill()) {
			Disease disease = patient->needs_cure_of();
			for (auto doctor = doctors.begin(); doctor != doctors.end(); ++doctor) {
				if (doctor->can_cure(disease)) {
					patient->cure_from(disease);
					patient->charge(dis(gen));
					doctor->pay(dis(gen)-10);
				}
			}
		}
	}
	collect_taxes(patients.begin(), patients.end());
	collect_taxes(doctors.begin(), doctors.end());
	list_stuff();
}

void Hospital::surcharge(Wallet &wallet) {
	std::random_device rd;
	std::uniform_int_distribution<> dis(1, 3);
	wallet.charge(dis(rd));
}

void Hospital::list_stuff() const {
	std::cout << "There are " << doctors.size() << " doctors:" << std::endl;
	for (auto it = doctors.cbegin(); it != doctors.cend(); ++it) {
		it->print_info();
	}
	std::cout << "There are " << patients.size() << " patients:" << std::endl;
	for (auto it = patients.cbegin(); it != patients.cend(); ++it) {
		it->print_info();
	}
}

Hospital& operator<< (Hospital &hospital,
                      const Patient &patient) {
	hospital.add(patient);
	return hospital;
}

Hospital& operator<< (Hospital &hospital,
                      const Doctor &doctor) {
	hospital.add(doctor);
	return hospital;
}
