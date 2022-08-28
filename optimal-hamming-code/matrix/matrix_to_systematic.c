#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <qc.h>
#include "matrix.h"

static ptrdiff_t find_systematic_column(bit *const* matrix, size_t num) {
    for (size_t i = 0; i < MATRIX_SIZE_N(matrix); ++i) {
        bool found = true;
        for (size_t j = 0; j < MATRIX_SIZE_M(matrix); ++j) {
            if (matrix[j][i] != (j == num ? 1 : 0)) {
                found = false;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

size_t* matrix_to_systematic(bit** matrix) {
    assert(MATRIX_SIZE_N(matrix) > MATRIX_SIZE_M(matrix));
    size_t* permutation = qc_malloc(MATRIX_SIZE_N(matrix) * sizeof(size_t));
    for (size_t i = 0; i < MATRIX_SIZE_N(matrix); ++i) {
        permutation[i] = i;
    }
    size_t tail = MATRIX_SIZE_N(matrix) - MATRIX_SIZE_M(matrix);
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        ptrdiff_t sys_index = find_systematic_column(matrix, i);
        assert(sys_index != -1);
        matrix_swap_columns(matrix, sys_index, tail);
        size_t tmp = permutation[sys_index];
        permutation[sys_index] = tail;
        permutation[tail] = tmp;
        ++tail;
    }
    return permutation;
}
