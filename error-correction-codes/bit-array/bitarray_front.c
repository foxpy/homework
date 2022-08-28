#include <stdint.h>
#include "bit-array.h"

bit bitarray_front(bits_t *bits) {
	uint8_t mask = 1;
	return bits->data[0] & mask;
}
