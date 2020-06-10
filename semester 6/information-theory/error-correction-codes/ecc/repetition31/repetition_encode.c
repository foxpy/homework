#include "bit-array.h"
#include "repetition-code.h"

void repetition_encode(bits_t *dst, bits_t *src) {
	while (!bitarray_empty(src)) {
		for (int i = 0; i < 3; ++i) bitarray_push_back(dst, bitarray_front(src));
		bitarray_pop_front(src);
	}
}
