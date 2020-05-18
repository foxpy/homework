#include "bit-array.h"
#include "hamming-code.h"
#include "hamming_impl.h"

void hamming_encode(bits_t *dst, bits_t *src) {
	bit a, b, c, d, x, y, z, p;
	while (!bitarray_empty(src)) {
		a = bitarray_next_front(src);
		b = bitarray_next_front(src);
		c = bitarray_next_front(src);
		d = bitarray_next_front(src);
		hamming84(a, b, c, d, &x, &y, &z, &p);
		bitarray_push_back(dst, a);
		bitarray_push_back(dst, b);
		bitarray_push_back(dst, c);
		bitarray_push_back(dst, d);
		bitarray_push_back(dst, x);
		bitarray_push_back(dst, y);
		bitarray_push_back(dst, z);
		bitarray_push_back(dst, p);
	}
}
