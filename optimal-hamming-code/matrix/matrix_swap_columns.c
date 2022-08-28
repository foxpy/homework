#include <stddef.h>
#include <assert.h>
#include "matrix.h"

void matrix_swap_columns(bit** matrix, size_t a, size_t b) {
    assert(a < MATRIX_SIZE_N(matrix));
    assert(b < MATRIX_SIZE_N(matrix));
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        bit tmp = matrix[i][a];
        matrix[i][a] = matrix[i][b];
        matrix[i][b] = tmp;
    }
}
