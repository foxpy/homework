#include <stdint.h>
#include "bit-array.h"

void bitarray_fill_from_memory(bits_t *dst, void *src, size_t nbits) {
	uint8_t *d = src;
	size_t nbytes = nbits / 8;
	nbits -= nbytes * 8;
	for (size_t i = 0; i < nbytes; ++i) {
		bitarray_push_back(dst, d[i] & 0x01u);
		bitarray_push_back(dst, d[i] & 0x02u);
		bitarray_push_back(dst, d[i] & 0x04u);
		bitarray_push_back(dst, d[i] & 0x08u);
		bitarray_push_back(dst, d[i] & 0x10u);
		bitarray_push_back(dst, d[i] & 0x20u);
		bitarray_push_back(dst, d[i] & 0x40u);
		bitarray_push_back(dst, d[i] & 0x80u);
	}
	if (nbits > 0) bitarray_push_back(dst, d[nbytes] & 0x01u);
	if (nbits > 1) bitarray_push_back(dst, d[nbytes] & 0x02u);
	if (nbits > 2) bitarray_push_back(dst, d[nbytes] & 0x04u);
	if (nbits > 3) bitarray_push_back(dst, d[nbytes] & 0x08u);
	if (nbits > 4) bitarray_push_back(dst, d[nbytes] & 0x10u);
	if (nbits > 5) bitarray_push_back(dst, d[nbytes] & 0x20u);
	if (nbits > 6) bitarray_push_back(dst, d[nbytes] & 0x40u);
	/*
	 * if (nbits > 7) bitarray_push_back(dst, d[nbytes] & 0x80u);
	 * commented line above makes no sense since a full byte
	 * is going to be copied by the first byte loop
	 */
}
