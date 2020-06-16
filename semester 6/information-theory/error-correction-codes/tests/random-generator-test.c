#ifdef NDEBUG
#undef NDEBUG
#endif

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "random.h"

int main() {
	rnd_state_t rnd;
	rnd_init(&rnd);
	uint8_t arru8[8];
	uint16_t arru16[8];
	uint32_t arru32[8];
	uint64_t arru64[8];
	float arrfp32[8];
	double arrfp64[8];
	double normaldistr[8];
	for (int i = 0; i < 8; ++i) {
		arru8[i] = rnd8(&rnd);
		arru16[i] = rnd16(&rnd);
		arru32[i] = rnd32(&rnd);
		arru64[i] = rnd64(&rnd);
		arrfp32[i] = rnd_fp32(&rnd);
		arrfp64[i] = rnd_fp64(&rnd);
		normaldistr[i] = normal_distribution(10.0, 5.0, &rnd);
		assert(arrfp32[i] >= 0.0f && arrfp32[i] < 1.0f);
		assert(arrfp64[i] >= 0.0 && arrfp64[i] < 1.0);
	}

	// This test has an extremely little chance (even if not zero) of failing on systems with
	// support for crypto-quality random, the chance is so low the hardware is more likely to fail.
	// The purpose of this test is to check if all random functions work as expected and are
	// seeded well. On unsupported platform seed equals 0 so xorshift produces all zeroes as output.
	assert(memcmp(&arru8[0], &arru8[4], 4 * sizeof(uint8_t)) != 0);
	assert(memcmp(&arru16[0], &arru16[4], 4 * sizeof(uint16_t)) != 0);
	assert(memcmp(&arru32[0], &arru32[4], 4 * sizeof(uint32_t)) != 0);
	assert(memcmp(&arru64[0], &arru64[4], 4 * sizeof(uint64_t)) != 0);
	assert(memcmp(&arrfp32[0], &arrfp32[4], 4 * sizeof(float)) != 0);
	assert(memcmp(&arrfp64[0], &arrfp64[4], 4 * sizeof(double)) != 0);
	assert(memcmp(&normaldistr[0], &normaldistr[4], 4 * sizeof(double)) != 0);
	return EXIT_SUCCESS;
}
