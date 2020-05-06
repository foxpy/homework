#include <stdint.h>
#include "bit-array.h"

void bitarray_fill_from_memory(bits_t *dst, void *src, size_t nbits) {
	uint8_t *d = src;
	size_t nbytes = nbits / 8;
	nbits -= nbytes * 8;
	for (size_t i = 0; i < nbytes; ++i) {
		bitarray_push_back(dst, d[i] & 0b00000001);
		bitarray_push_back(dst, d[i] & 0b00000010);
		bitarray_push_back(dst, d[i] & 0b00000100);
		bitarray_push_back(dst, d[i] & 0b00001000);
		bitarray_push_back(dst, d[i] & 0b00010000);
		bitarray_push_back(dst, d[i] & 0b00100000);
		bitarray_push_back(dst, d[i] & 0b01000000);
		bitarray_push_back(dst, d[i] & 0b10000000);
	}
	if (nbits > 0) bitarray_push_back(dst, d[nbytes] & 0b00000001);
	if (nbits > 1) bitarray_push_back(dst, d[nbytes] & 0b00000010);
	if (nbits > 2) bitarray_push_back(dst, d[nbytes] & 0b00000100);
	if (nbits > 3) bitarray_push_back(dst, d[nbytes] & 0b00001000);
	if (nbits > 4) bitarray_push_back(dst, d[nbytes] & 0b00010000);
	if (nbits > 5) bitarray_push_back(dst, d[nbytes] & 0b00100000);
	if (nbits > 6) bitarray_push_back(dst, d[nbytes] & 0b01000000);
	/*
	 * if (nbits > 7) bitarray_push_back(dst, d[nbytes] & 0b10000000);
	 * commented line above makes no sense since a full byte
	 * is going to be copied by the first byte loop
	 */
}
