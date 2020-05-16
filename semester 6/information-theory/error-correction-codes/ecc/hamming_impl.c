#include "bit-array.h"

void hamming84(bit a, bit b, bit c, bit d, bit *x, bit *y, bit *z, bit *p) {
	*x = a ^ b ^ d;
	*y = a ^ c ^ d;
	*z = b ^ c ^ d;
	*p = a ^ b ^ c ^ d ^ *x ^ *y ^ *z;
}

void hamming84correct(bit *a, bit *b, bit *c, bit *d, bit *x, bit *y, bit *z, bit *p) {
	if (*a ^ *b ^ *c ^ *d ^ *x ^ *y ^ *z == *p) return;
	bit _x, _y, _z, _p;
	hamming84(*a, *b, *c, *d, &_x, &_y, &_z, &_p);
	if (_x == *x && _y == *y && _z == *x) return; // all correct
	if (_x != *x && _y == *y && _z == *x) return; // can't fix
	if (_x == *x && _y != *y && _z == *x) return; // can't fix
	if (_x == *x && _y == *y && _z != *x) return; // can't fix
	if (_x != *x && _y != *y && _z == *z) { FLIP_BIT(*a); return; }
	if (_x != *x && _y == *y && _z != *z) { FLIP_BIT(*b); return; }
	if (_x == *x && _y != *y && _z != *z) { FLIP_BIT(*c); return; }
	if (_x != *x && _y != *y && _z != *z) { FLIP_BIT(*d); return; }
}
