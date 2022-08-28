#include <assert.h>
#include <stddef.h>
#include "matrix.h"

bit** matrix_multiply(bit *const* A, bit *const* B) {
    assert(MATRIX_SIZE_N(A) == MATRIX_SIZE_M(B));
    bit** ret = matrix_new(MATRIX_SIZE_M(A), MATRIX_SIZE_N(B));
    for (size_t i = 0; i < MATRIX_SIZE_M(A); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(B); ++j) {
            for (size_t k = 0; k < MATRIX_SIZE_N(A); ++k) {
                ret[i][j] ^= (bit) (A[i][k] * B[k][j]);
            }
        }
    }
    return ret;
}
