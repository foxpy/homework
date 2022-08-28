#include <stdbool.h>
#include "bit-array.h"

bool bitarray_empty(bits_t *bits) {
	return bitarray_size(bits) == 0;
}
