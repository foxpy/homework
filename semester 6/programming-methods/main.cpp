#include <vector>

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
}
