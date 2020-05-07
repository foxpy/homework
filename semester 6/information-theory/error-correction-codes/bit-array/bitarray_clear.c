#include "bit-array.h"

void bitarray_clear(bits_t *bits) {
	while (!bitarray_empty(bits)) bitarray_pop_back(bits);
}
