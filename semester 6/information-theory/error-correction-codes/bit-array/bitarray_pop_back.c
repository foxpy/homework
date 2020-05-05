#include "bit-array.h"
#include "emalloc.h"

void bitarray_pop_back(bits_t *bits) {
	if (bits->bit == 0) {
		bits->bit = 8;
		--(bits->len);
		if (bits->cap > 2 && bits->cap / 2 > bits->len) {
			bits->cap /= 2;
			bits->data = erealloc(bits->data, bits->cap);
		}
	}
	--(bits->bit);
}
