#include "matrix.h"

bit** matrix_transpose(bit** matrix) {
    bit** ret = matrix_new(MATRIX_SIZE_N(matrix), MATRIX_SIZE_M(matrix));
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(matrix); ++j) {
            ret[j][i] = matrix[i][j];
        }
    }
    matrix_free(matrix);
    return ret;
}
