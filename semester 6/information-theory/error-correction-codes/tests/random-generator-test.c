#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "random.h"

int main() {
	uint32_t arru32[8];
	uint64_t arru64[8];
	for (int i = 0; i < 8; ++i) {
		arru32[i] = rnd32();
		arru64[i] = rnd64();
	}

	// This test has an extremely little chance (even if not zero) of failing on systems with
	// support for crypto-quality random, the chance is so low the hardware is more likely to fail.
	// The purpose of this test is to check if random works and produces at least pseudorandom numbers.
	assert(memcmp(&arru32[0], &arru32[4], 4 * sizeof(uint32_t)) != 0);
	assert(memcmp(&arru64[0], &arru64[4], 4 * sizeof(uint64_t)) != 0);
	return EXIT_SUCCESS;
}
