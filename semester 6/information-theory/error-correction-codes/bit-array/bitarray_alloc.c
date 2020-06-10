#include <string.h>
#include "bit-array.h"
#include "util.h"

void bitarray_alloc(bits_t *bits) {
	bits->len = 0;
	bits->cap = 2;
	bits->bit = 0;
	bits->data = (uint8_t*) emalloc(2);
}
