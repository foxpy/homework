#include <stdint.h>
#include "bit-array.h"
#include "util.h"

void bitarray_push_back(bits_t *bits, bit b) {
	if (bits->bit == 8) {
		bits->bit = 0;
		++(bits->len);
	}
	if (bits->len == bits->cap) {
		bits->cap *= 2;
		bits->data = (uint8_t*) erealloc(bits->data, bits->cap);
	}
	uint8_t mask = 1;
	mask <<= bits->bit;
	if (b)
		bits->data[bits->len] |= mask;
	else
		bits->data[bits->len] &= ~mask;
	++(bits->bit);
}
