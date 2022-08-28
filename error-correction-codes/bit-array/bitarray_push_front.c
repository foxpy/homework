#include <stdint.h>
#include <stdlib.h>
#include "bit-array.h"

void bitarray_push_front(bits_t *bits, bit b) {
	uint8_t mask = 1;
	uint8_t cmask = 1 << 7;
	bit carry;
	bitarray_push_back(bits, 0);
	size_t len = bits->len;

	do {
		if (len > 0) {
			carry = bits->data[len-1] & cmask;
		} else {
			carry = 0;
		}
		bits->data[len] <<= 1;
		if (carry)
			bits->data[len] |= mask;
		else
			bits->data[len] &= ~mask;
	} while (len--);

	if (b)
		bits->data[0] |= mask;
	else
		bits->data[0] &= ~mask;
}
