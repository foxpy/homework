#include "util.h"

unsigned lcm(unsigned a, unsigned b) {
	return a * b / gcd(a, b);
}
