#include <stdint.h>
#include "bit-array.h"
#include "repetition-code.h"

static bit decode_next(bits_t *bits) {
	uint8_t sum = 0;
	for (int i = 0; i < 3; ++i) {
		if (bitarray_empty(bits)) {
			sum += 0;
		} else {
			sum += bitarray_front(bits);
			bitarray_pop_front(bits);
		}
	}
	return (sum > 1) ? 1 : 0;
}

void repetition_decode(bits_t *dst, bits_t *src) {
	while (!bitarray_empty(src)) {
		bitarray_push_back(dst, decode_next(src));
	}
}
