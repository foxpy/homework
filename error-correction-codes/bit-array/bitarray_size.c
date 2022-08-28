#include <stdlib.h>
#include "bit-array.h"

size_t bitarray_size(bits_t *bits) {
	return bits->len * 8 + bits->bit;
}
