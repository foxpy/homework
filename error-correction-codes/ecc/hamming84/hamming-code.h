#pragma once
#include "bit-array.h"

size_t hamming_encode(bits_t *dst, bits_t *src);
size_t hamming_decode(bits_t *dst, bits_t *src);
