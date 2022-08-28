#include <stdint.h>
#include "bit-array.h"

bit bitarray_back(bits_t *bits) {
	uint8_t mask = 1;
	if (bits->bit != 0) {
		mask <<= bits->bit-1;
		return bits->data[bits->len] & mask;
	} else {
		mask <<= 7;
		return bits->data[bits->len-1] & mask;
	}
}
