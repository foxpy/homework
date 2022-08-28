#include "hamming.h"

bit** hamming_H(size_t n, size_t k) {
    bit** ret = matrix_new(n - k, n);
    size_t step = 0;
    for (size_t i = 0; i < MATRIX_SIZE_N(ret); ++i) {
        ++step;
        for (size_t j = 0; j < MATRIX_SIZE_M(ret); ++j) {
            size_t mask = 1u << (MATRIX_SIZE_M(ret) - j - 1);
            ret[j][i] = step & mask;
        }
    }
    return ret;
}
