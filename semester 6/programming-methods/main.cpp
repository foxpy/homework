#include <vector>
#include <iostream>

#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"
#include "disease.hpp"

int main() {
	Hospital hospital("Yellow house");
	Doctor doctor1("Mike", 34);
	Doctor doctor2("Alex", 22, (const std::vector<Disease>) {Disease::Hepatisis});
	Patient patient1("John", 23);
	Patient patient2("Carl", 30, (const std::vector<Disease>) {Disease::Alzheimer});
	hospital.add_doctor(doctor1);
	hospital.add_patient(patient2);
	std::cout << "Patient " << patient1.name() << " is " << ((patient1.is_ill()) ? "ill" : "healthy") << std::endl;
	std::cout << "Patient " << patient2.name() << " is " << ((patient2.is_ill()) ? "ill" : "healthy") << std::endl;
}
