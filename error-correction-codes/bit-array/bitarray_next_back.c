#include "bit-array.h"

bit bitarray_next_back(bits_t *bits) {
	bit b;
	if (bitarray_empty(bits)) {
		return 0;
	} else {
		b = bitarray_back(bits);
		bitarray_pop_back(bits);
		return b;
	}
}
