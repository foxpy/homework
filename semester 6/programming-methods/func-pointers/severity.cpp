#include <ostream>
#include "function-pointers.hpp"

static const char* const SeverityNames[] = {
	"Low severity",
	"Medium severity",
	"High severity",
	"Extreme severity",
};

std::ostream& operator<< (std::ostream &o, Severity s) {
	return o << SeverityNames[s];
}
