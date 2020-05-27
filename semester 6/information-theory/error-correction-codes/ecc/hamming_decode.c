#include "bit-array.h"
#include "hamming-code.h"
#include "hamming_impl.h"

void hamming_decode(bits_t *dst, bits_t *src) {
	bit a, b, c, d, x, y, z, p;
	while (bitarray_size(src) >= 8) {
		a = bitarray_next_front(src);
		b = bitarray_next_front(src);
		c = bitarray_next_front(src);
		d = bitarray_next_front(src);
		x = bitarray_next_front(src);
		y = bitarray_next_front(src);
		z = bitarray_next_front(src);
		p = bitarray_next_front(src);
		hamming84correct(&a, &b, &c, &d, &x, &y, &z, &p);
		bitarray_push_back(dst, a);
		bitarray_push_back(dst, b);
		bitarray_push_back(dst, c);
		bitarray_push_back(dst, d);
	}
}
