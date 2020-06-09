#pragma once
#include "hamming-code.h"

void hamming84(bit a, bit b, bit c, bit d, bit *x, bit *y, bit *z, bit *p);
int hamming84correct(bit *a, bit *b, bit *c, bit *d, bit *x, bit *y, bit *z, bit *p);
