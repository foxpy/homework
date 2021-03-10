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

size_t ticks(gost* g, uint32_t buf[2]) {
	unsigned lo0 = 0, hi0 = 0;
	unsigned lo1 = 0, hi1 = 0;
	__asm__ __volatile__ (
		"lfence;rdtsc" : "=a"(lo0), "=d"(hi0) : : "memory"
	);
	gost_encrypt(g, buf, 2);
	__asm__ __volatile__ (
		"lfence;rdtsc" : "=a"(lo1), "=d"(hi1) : : "memory"
	);
	unsigned long start = lo0 | ((unsigned long) hi0 << 32);
	unsigned long end = lo1 | ((unsigned long) hi1 << 32);
	return end - start;
}

#define NUM_SAMPLES 100

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
	printf("Output data: %s\n", (char*) data);

	size_t samples[NUM_SAMPLES] = {0};
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		samples[i] = ticks(&g, data);
	}
	size_t min = SIZE_MAX, max = 0;
	double sum = 0.0;
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		if (samples[i] > max) max = samples[i];
		if (samples[i] < min) min = samples[i];
		sum += samples[i];
		printf("Run %8zu, time: %8zu\n", i, samples[i]);
	}
	double avg = sum / NUM_SAMPLES;
	double disp = 0.0;
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		disp += pow(avg - samples[i], 2);
	}
	disp /= NUM_SAMPLES;
	double std = sqrt(disp);
	printf("Min: %zu, max: %zu, avg: %.0f, dev: %.2f, std: %.2f\n",
			min, max, avg, disp, std);

	return EXIT_SUCCESS;
}
