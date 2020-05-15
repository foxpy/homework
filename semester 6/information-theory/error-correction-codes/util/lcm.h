#pragma once
#include "gcd.h"

static unsigned lcm(unsigned a, unsigned b) {
	return a * b / gcd(a, b);
}
