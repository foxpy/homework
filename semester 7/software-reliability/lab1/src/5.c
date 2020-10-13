#include <stddef.h>

double lab5(double const X[static 20], double const Y[static 20]) {
	double sum1 = 0.0, sum2 = 0.0;
	for (size_t i = 1; i <= 15; ++i) {
		sum1 += X[i] * Y[i];
	}
	if (sum1 > 0.0) {
		for (size_t i = 0; i <= 19; ++i) {
			sum2 += X[i] * X[i];
		}
	} else {
		for (size_t i = 10; i <= 19; ++i) {
			sum2 += Y[i] * Y[i];
		}
	}
	return sum2;
}
