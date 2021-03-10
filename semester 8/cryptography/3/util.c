#include "gost.h"

uint32_t rotl32(uint32_t x, size_t n) {
	return x << n | x >> (32 - n);
}

uint32_t f(gost* g, uint32_t x) {
	x = g->k87[x>>24 & 255] << 24
	  | g->k65[x>>16 & 255] << 16
	  | g->k43[x>>16 & 255] << 8
	  | g->k21[x & 255];
	return rotl32(x, 11);
}

void die(char const* msg) {
	fprintf(stderr, "Fatal error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void print_key(uint32_t const key[8]) {
	uint8_t const* k = (uint8_t const*) key;
	printf("GOST key: 0x");
	for (size_t i = 0; i < 8 * sizeof(uint32_t); ++i)
		printf("%02" PRIx8, k[i]);
	printf("\n");
}
