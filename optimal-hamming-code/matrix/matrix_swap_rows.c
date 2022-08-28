#include <stddef.h>
#include <assert.h>
#include "matrix.h"

void matrix_swap_rows(bit** matrix, size_t a, size_t b) {
    assert(a < MATRIX_SIZE_M(matrix));
    assert(b < MATRIX_SIZE_M(matrix));
    bit* tmp = matrix[a];
    matrix[a] = matrix[b];
    matrix[b] = tmp;
}
