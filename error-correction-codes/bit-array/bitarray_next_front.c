#include "bit-array.h"

bit bitarray_next_front(bits_t *bits) {
	bit b;
	if (bitarray_empty(bits)) {
		return 0;
	} else {
		b = bitarray_front(bits);
		bitarray_pop_front(bits);
		return b;
	}
}
