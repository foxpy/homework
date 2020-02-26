#include <ostream>

#include "disease.hpp"

std::ostream& operator<< (std::ostream &o, Disease d) {
	return o << DiseaseNames[d];
}
