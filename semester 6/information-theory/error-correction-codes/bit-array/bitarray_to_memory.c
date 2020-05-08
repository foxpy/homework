#include <string.h>
#include <stdint.h>
#include "bit-array.h"
#include "emalloc.h"

void* bitarray_to_memory(bits_t *src, size_t *nbits, size_t *nbytes) {
	*nbits = bitarray_size(src);
	*nbytes = *nbits / 8;
	*nbytes += (*nbits % 8) ? 1 : 0;
	uint8_t *new_memory = emalloc(*nbytes);
	memset(new_memory, 0, *nbytes);

	uint8_t mask;
	for (size_t i = 0; i < *nbytes; ++i) {
		for (uint8_t bit = 0; bit < 8; ++bit) {
			if (!bitarray_empty(src)) {
				mask = 1 << bit;
				if (bitarray_front(src))
					new_memory[i] |= mask;
				else
					new_memory[i] &= ~mask;
				bitarray_pop_front(src);
			} else {
				break;
			}
		}
	}
	bitarray_free(src);
	return new_memory;
}
