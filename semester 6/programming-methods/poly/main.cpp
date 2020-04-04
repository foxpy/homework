#include <iostream>
#include <vector>
#include "hospital.hpp"
#include "patient.hpp"
#include "doctor.hpp"
#include "disease.hpp"

int main() {
	Hospital hospital("Yellow house");
	hospital << Doctor("Maria",  35, (std::vector<Disease>) {Disease::NeckPain,
	                                                         Disease::Headache,
	                                                         Disease::Flu})
	         << Doctor("Mike",   47, (std::vector<Disease>) {Disease::Asthma})
	         << Doctor("Carl",   36, (std::vector<Disease>) {Disease::Cancer,
	                                                         Disease::Diarrhea,
	                                                         Disease::Hepatisis})
	         << Patient("Alex",  23, (std::vector<Disease>) {Disease::Headache,
	                                                         Disease::Flu})
	         << Patient("Smith", 63, (std::vector<Disease>) {Disease::Headache,
	                                                         Disease::NeckPain,
	                                                         Disease::Asthma,
	                                                         Disease::Diarrhea})
	         << Patient("Adam",  13, (std::vector<Disease>) {Disease::Cancer})
	         << Patient("Nick",  26, (std::vector<Disease>) {Disease::Hepatisis})
	         << Patient("Tom",   31, (std::vector<Disease>) {Disease::Headache,
	                                                         Disease::Hepatisis});
	hospital.run();
}
