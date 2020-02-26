#include <vector>

#include "hospital.hpp"
#include "doctor.hpp"
#include "patient.hpp"
#include "disease.hpp"

int main() {
	Hospital hospital;
	Doctor doctor("Mike", 34);
	Patient patient1("John", 23);
	Patient patient2("Carl", 30, (const std::vector<Disease>) {Disease::Alzheimer});
}
