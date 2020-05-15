#pragma once

static unsigned gcd(unsigned a, unsigned b) {
	if (a == b) return a;
	if (a > b)
		return gcd(a - b, b);
	else
		return gcd(a, b - a);
}
