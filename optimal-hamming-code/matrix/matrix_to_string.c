#include <qc.h>
#include "matrix.h"

char* matrix_to_string(bit *const* matrix) {
    size_t alloc_size = 2 * (MATRIX_SIZE_M(matrix) * MATRIX_SIZE_N(matrix) - 1) + 1
                        + MATRIX_SIZE_M(matrix)
                        + 1;
    char* ret = qc_malloc(alloc_size);
    size_t current_char = 0;
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(matrix); ++j) {
            ret[current_char++] = matrix[i][j] ? '1' : '0';
            ret[current_char++] = ' ';
        }
        ret[--current_char] = '\n';
        ++current_char;
    }
    ret[current_char] = '\0';
    return ret;
}
