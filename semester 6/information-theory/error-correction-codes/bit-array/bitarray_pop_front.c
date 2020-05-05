#include <stdint.h>
#include "bit-array.h"

void bitarray_pop_front(bits_t *bits) {
	uint8_t mask = 1 << 7;
	uint8_t cmask = 1;
	bit carry;
	if (bits->len > 0) for (size_t i = 0; i < bits->len; ++i) {
		carry = bits->data[i+1] & cmask;
		bits->data[0] >>= 1;
		if (carry)
			bits->data[i] |= mask;
		else
			bits->data[i] &= ~mask;
	}
	bits->data[bits->len] >>= 1;
	bitarray_pop_back(bits);
}
