#include <iostream>

#include "hospital.hpp"
#include "disease.hpp"

int main() {
	Hospital hospital;
	Disease disease = Disease::Acne;
	std::cout << "Created disease " << disease << std::endl;
}
