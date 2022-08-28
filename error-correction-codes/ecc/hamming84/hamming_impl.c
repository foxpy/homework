#include "bit-array.h"

void hamming84(bit a, bit b, bit c, bit d, bit *x, bit *y, bit *z, bit *p) {
	*x = a ^ b ^ d;
	*y = a ^ c ^ d;
	*z = b ^ c ^ d;
	*p = a ^ b ^ c ^ d ^ *x ^ *y ^ *z;
}

int hamming84correct(bit *a, bit *b, bit *c, bit *d, bit *x, bit *y, bit *z, bit *p) {
	bit _x, _y, _z, _p;
	hamming84(*a, *b, *c, *d, &_x, &_y, &_z, &_p);
	if ((*a ^ *b ^ *c ^ *d ^ *x ^ *y ^ *z) != *p) {
		if (_x == *x && _y == *y && _z == *z) return 0;
		else if (_x != *x && _y == *y && _z == *z) { FLIP_BIT(*x); return 0; }
		else if (_x == *x && _y != *y && _z == *z) { FLIP_BIT(*y); return 0; }
		else if (_x == *x && _y == *y && _z != *z) { FLIP_BIT(*z); return 0; }
		else if (_x != *x && _y != *y && _z == *z) { FLIP_BIT(*a); return 0; }
		else if (_x != *x && _y == *y && _z != *z) { FLIP_BIT(*b); return 0; }
		else if (_x == *x && _y != *y && _z != *z) { FLIP_BIT(*c); return 0; }
		else /* if (_x != *x && _y != *y && _z != *z) */ { FLIP_BIT(*d); return 0; }
	} else {
		if (_x == *x && _y == *y && _z == *z) { FLIP_BIT(*p); return 0; }
		else return 1; // 2 or more errors, can't correct
	}
}
