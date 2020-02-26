#include <vector>

#include "hospital.hpp"
#include "patient.hpp"
#include "disease.hpp"

int main() {
	Hospital hospital;
	Patient patient1("John", 23);
	Patient patient2("Carl", 30, (const std::vector<Disease>) {Disease::Alzheimer});
}
