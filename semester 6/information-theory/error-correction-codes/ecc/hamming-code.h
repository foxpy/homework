#pragma once
#include "bit-array.h"

void hamming_encode(bits_t *dst, bits_t *src);
void hamming_decode(bits_t *dst, bits_t *src);
