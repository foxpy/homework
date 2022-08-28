#include <stddef.h>
#include <string.h>
#include <qc.h>
#include "matrix.h"

static void iteration(size_t m, size_t n) {
    bit** mat1 = matrix_new(m, n);
    matrix_fill_random(mat1);
    bit** mat2 = matrix_clone(mat1);
    char* mat1_str = matrix_to_string(mat1);
    char* mat2_str = matrix_to_string(mat2);
    qc_assert(strcmp(mat1_str, mat2_str) == 0, "Cloned matrix is different");
    free(mat1_str);
    free(mat2_str);
    matrix_free(mat1);
    matrix_free(mat2);
}

int main() {
    for (size_t i = 1; i < 10; ++i) {
        for (size_t j = 1; j < 10; ++j) {
            iteration(i, j);
        }
    }
}
