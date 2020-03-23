#include <vector>
#include <iostream>

#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"
#include "disease.hpp"

int main() {
	Hospital hospital("Yellow house");
	Doctor doctor1;
	Doctor doctor2("Mike", 34, (const std::vector<Disease>) {Disease::Hepatisis});
	Patient patient1;
	Patient patient2("John", 23, (const std::vector<Disease>) {Disease::Alzheimer});
	hospital.add_doctor(doctor1);
	hospital << doctor2;
	hospital.add_patient(patient2);
	Hospital another_hospital(hospital);
	Hospital yet_another_hospital(another_hospital);
	Doctor mutant(patient2);
	std::cout << "Doctor " << mutant.name() << ' ' << ((mutant.can_cure(Disease::Alzheimer)) ? "can" : "can't")
	          << " cure disease " << Disease::Alzheimer << std::endl;
	yet_another_hospital << patient1 << patient2;
	std::cout << "Patient " << patient1.name() << " is " << ((patient1.is_ill()) ? "ill" : "healthy") << std::endl;
	std::cout << "Patient " << patient2.name() << " is " << ((patient2.is_ill()) ? "ill" : "healthy") << std::endl;
	std::cout << "Doctor " << doctor2.name() << ' ' << ((doctor2.can_cure(Disease::Flu)) ? "can" : "can't")
	          << " cure disease " << Disease::Flu << std::endl;
	std::cout << "Doctor " << doctor2.name() << ' ' << ((doctor2.can_cure(Disease::Hepatisis)) ? "can" : "can't")
	          << " cure disease " << Disease::Hepatisis << std::endl;
	doctor1.pay(10);
	doctor1.charge(20);
	patient1.pay(5);
	patient1.charge(25);
}
