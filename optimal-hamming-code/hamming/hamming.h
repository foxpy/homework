#pragma once
#include <stddef.h>
#include "matrix.h"

size_t hamming_n(size_t k);
bit** hamming_H(size_t n, size_t k);
bit** hamming_G(bit *const* H);
