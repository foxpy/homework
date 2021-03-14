#include <math.h>
#include "gost.h"

static size_t round_size(size_t x, size_t m) {
	if (m == 0) return x;
	size_t r = x % m;
	if (r == 0) return x;
	return x + m - r;
}

static void print_data(char const* header, uint8_t* buf, size_t len) {
	printf("%s: 0x", header);
	for (size_t i = 0; i < len; ++i) {
		printf("%02" PRIx8, buf[i]);
	}
	printf("\n");
}

static size_t get_input(uint32_t** dst, int argc, char** argv) {
	if (argc != 2) {
		die("Invalid usage");
	} else {
		printf("Input string: %s\n", argv[1]);
		size_t len = round_size(strlen(argv[1]) + 1, 8);
		*dst = malloc(len);
		memset(*dst, 0, len);
		strcpy((char*) *dst, argv[1]);
		return len / 8;
	}
}

size_t ecb_ticks(gost* g, volatile uint32_t buf[2]) {
	unsigned lo0 = 0, hi0 = 0;
	unsigned lo1 = 0, hi1 = 0;
	__asm__ __volatile__ (
		"lfence;rdtsc" : "=a"(lo0), "=d"(hi0) : : "memory"
	);
	gost_encrypt(g, (uint32_t*) buf, 2);
	__asm__ __volatile__ (
		"lfence;rdtsc" : "=a"(lo1), "=d"(hi1) : : "memory"
	);
	unsigned long start = lo0 | ((unsigned long) hi0 << 32);
	unsigned long end = lo1 | ((unsigned long) hi1 << 32);
	return end - start;
}

size_t cbc_ticks(gost* g, volatile uint32_t iv[2], volatile uint32_t buf[2]) {
	unsigned lo0 = 0, hi0 = 0;
	unsigned lo1 = 0, hi1 = 0;
	__asm__ __volatile__ (
		"lfence;rdtsc" : "=a"(lo0), "=d"(hi0) : : "memory"
	);
	buf[0] ^= iv[0]; buf[1] ^= iv[1];
	gost_encrypt(g, (uint32_t*) buf, 2);
	iv[0] = buf[0]; iv[1] = buf[1];
	__asm__ __volatile__ (
		"lfence;rdtsc" : "=a"(lo1), "=d"(hi1) : : "memory"
	);
	unsigned long start = lo0 | ((unsigned long) hi0 << 32);
	unsigned long end = lo1 | ((unsigned long) hi1 << 32);
	return end - start;
}

#define WARMUP_ITERATIONS 1000
#define NUM_SAMPLES 200

int main(int argc, char* argv[]) {
	uint32_t* data;
	size_t len = get_input(&data, argc, argv);
	uint32_t key[8];
	gost g;
	gost_init(&g);
	gost_key(&g, key);
	print_key(key);

	print_data("Input data", (uint8_t*) data, len * 8);
	gost_encrypt(&g, data, len);
	print_data("Ciphertext", (uint8_t*) data, len * 8);
	gost_decrypt(&g, data, len);
	print_data("Plaintext", (uint8_t*) data, len * 8);
	printf("Output string: %s\n", (char*) data);

	size_t ecb_samples[NUM_SAMPLES] = {0};
	for (size_t i = 0; i < WARMUP_ITERATIONS; ++i) {
		ecb_ticks(&g, data);
	}
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		ecb_samples[i] = ecb_ticks(&g, data);
	}
	size_t min = SIZE_MAX, max = 0;
	double sum = 0.0;
	printf("\nECB Samples: ");
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		if (ecb_samples[i] > max) max = ecb_samples[i];
		if (ecb_samples[i] < min) min = ecb_samples[i];
		sum += ecb_samples[i];
		printf("%zu, ", ecb_samples[i]);
	}
	printf("\n");
	double avg = sum / NUM_SAMPLES;
	double std = 0.0;
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		std += pow(avg - ecb_samples[i], 2);
	}
	std /= NUM_SAMPLES;
	std = sqrt(std);
	printf("Min: %zu, max: %zu, avg: %.0f, stddev: %.2f\n",
			min, max, avg, std);

	uint32_t iv[2];
	memmove(iv, key, sizeof(uint32_t) * 2);
	gost_key(&g, key);
	size_t cbc_samples[NUM_SAMPLES] = {0};
	for (size_t i = 0; i < WARMUP_ITERATIONS; ++i) {
		cbc_ticks(&g, iv, data);
	}
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		cbc_samples[i] = cbc_ticks(&g, iv, data);
	}
	min = SIZE_MAX, max = 0;
	sum = 0.0;
	printf("\nCBC Samples: ");
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		if (cbc_samples[i] > max) max = cbc_samples[i];
		if (cbc_samples[i] < min) min = cbc_samples[i];
		sum += cbc_samples[i];
		printf("%zu, ", cbc_samples[i]);
	}
	printf("\n");
	avg = sum / NUM_SAMPLES;
	std = 0.0;
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		std += pow(avg - cbc_samples[i], 2);
	}
	std /= NUM_SAMPLES;
	std = sqrt(std);
	printf("Min: %zu, max: %zu, avg: %.0f, stddev: %.2f\n",
			min, max, avg, std);

	return EXIT_SUCCESS;
}
