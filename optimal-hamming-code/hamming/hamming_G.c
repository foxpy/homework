#include <stddef.h>
#include <stdlib.h>
#include "hamming.h"

bit** hamming_G(bit *const* H) {
    bit** Hsys = matrix_clone(H);
    size_t* permutation = matrix_to_systematic(Hsys);
    size_t n = MATRIX_SIZE_N(Hsys);
    size_t k = n - MATRIX_SIZE_M(Hsys);
    bit** G = matrix_new(n, k);
    for (size_t i = 0; i < k; ++i) {
        G[i][i] = 1;
    }
    for (size_t i = 0; i < n - k; ++i) {
        for (size_t j = 0; j < k; ++j) {
            G[k + i][j] = Hsys[i][j];
        }
    }
    bit** Gperm = matrix_new(MATRIX_SIZE_M(G), MATRIX_SIZE_N(G));
    for (size_t i = 0; i < MATRIX_SIZE_M(G); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(G); ++j) {
            Gperm[permutation[i]][j] = G[i][j];
        }
    }
    matrix_free(G);
    free(permutation);
    matrix_free(Hsys);
    return Gperm;
}
