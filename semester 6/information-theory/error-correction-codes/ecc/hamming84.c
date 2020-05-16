#include "bit-array.h"

void hamming84(bit a, bit b, bit c, bit d, bit *x, bit *y, bit *z, bit *p) {
	*x = a ^ b ^ d;
	*y = a ^ c ^ d;
	*z = b ^ c ^ d;
	*p = a ^ b ^ c ^ d ^ *x ^ *y ^ *z;
}
