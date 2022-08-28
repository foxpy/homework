#include <stdlib.h>
#include "bit-array.h"

void bitarray_free(bits_t *bits) {
	bits->len = 0;
	bits->cap = 0;
	bits->bit = 0;
	free(bits->data);
	bits->data = NULL;
}
