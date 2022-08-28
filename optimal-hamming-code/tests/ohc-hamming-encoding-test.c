#include <stddef.h>
#include <qc.h>
#include "matrix.h"
#include "hamming.h"

static void assert_matrix_zero(bit *const* mat) {
    for (size_t i = 0; i < MATRIX_SIZE_M(mat); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(mat); ++j) {
            qc_assert(mat[i][j] == 0, "Matrix is not a zero matrix");
        }
    }
}

static void iteration(size_t k) {
    size_t n = hamming_n(k);
    bit** H = hamming_H(n, k);
    bit** G = hamming_G(H);
    bit** I = matrix_new(k, 1);
    matrix_fill_random(I);
    bit** C = matrix_multiply(G, I);
    bit** S = matrix_multiply(H, C);
    assert_matrix_zero(S);
    matrix_free(S);
    matrix_free(C);
    matrix_free(I);
    matrix_free(G);
    matrix_free(H);
}

int main() {
    qc_rnd rnd;
    qc_rnd_init(&rnd, NULL);
    iteration(4);
    iteration(11);
    iteration(26);
}
