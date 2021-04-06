#include <stddef.h>
#include <stdio.h>
#define P 23

int main(void) {
	unsigned Y[P];
	unsigned X[P];
	for (size_t i = 0; i < P; ++i) {
		Y[i] = (i*i) % P;
		X[i] = (i*i*i + i + 1) % P;
	}
	for (size_t i = 0; i < P; ++i) {
		for (size_t j = 0; j < P; ++j) {
			if (X[i] == Y[j]) printf("P(%u;%u)\n", i, j);
		}
	}
}
