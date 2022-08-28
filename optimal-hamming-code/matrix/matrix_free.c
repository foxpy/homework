#include <stddef.h>
#include <stdlib.h>
#include "matrix.h"

void matrix_free(bit** matrix) {
    size_t* mem = (size_t*) matrix;
    mem -= 2;
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        free(matrix[i]);
    }
    free(mem);
}
