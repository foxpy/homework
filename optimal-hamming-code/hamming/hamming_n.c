#include <stddef.h>
#include <assert.h>
#include "hamming.h"

static size_t powu(size_t x, size_t n) {
    size_t ret = 1;
    for (size_t i = 0; i < n; ++i) {
        ret *= x;
    }
    return ret;
}

static void hamming_parameters(size_t s, size_t *n, size_t *k) {
    *n = powu(2, s) - 1;
    *k = *n - s;
}

size_t hamming_n(size_t target_k) {
    assert(target_k != 0);
    size_t s = 0, n = 0, k = 0;
    while (k < target_k) {
        ++s;
        hamming_parameters(s, &n, &k);
    }
    return n - k + target_k;
}
