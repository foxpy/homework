#include "matrix.h"

bit** matrix_clone(bit *const* matrix) {
    bit** ret = matrix_new(MATRIX_SIZE_M(matrix), MATRIX_SIZE_N(matrix));
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(matrix); ++j) {
            ret[i][j] = matrix[i][j];
        }
    }
    return ret;
}
