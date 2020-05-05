#include <stdint.h>
#include <string.h>
#include "bit-array.h"
#include "emalloc.h"

void bitarray_copy(bits_t *dst, bits_t *src) {
	dst->data = (uint8_t*) emalloc(src->cap);
	memcpy(dst->data, src->data, src->cap);
	dst->len = src->len;
	dst->cap = src->cap;
	dst->bit = src->bit;
}
