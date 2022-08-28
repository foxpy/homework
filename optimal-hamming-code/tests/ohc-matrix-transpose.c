#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <qc.h>
#include "matrix.h"

static void test1() {
    bit** mat = matrix_new(4, 2);
    mat[0][0] = 0; mat[0][1] = 1;
    mat[1][0] = 0; mat[1][1] = 0;
    mat[2][0] = 1; mat[2][1] = 1;
    mat[3][0] = 0; mat[3][1] = 0;
    mat = matrix_transpose(mat);
    char const* expected = "0 0 1 0\n1 0 1 0\n";
    char* actual = matrix_to_string(mat);
    qc_assert(strcmp(expected, actual) == 0, "Expected: \"%s\", got: \"%s\"", expected, actual);
    free(actual);
    matrix_free(mat);
}

static  void iteration(size_t m, size_t n) {
    bit** original = matrix_new(m, n);
    matrix_fill_random(original);
    bit** transposed = matrix_transpose(matrix_clone(original));
    bit ** transposed_twice = matrix_transpose(transposed);
    char* original_str = matrix_to_string(original);
    char* transposed_twice_str = matrix_to_string(transposed_twice);
    qc_assert(strcmp(original_str, transposed_twice_str) == 0,
                     "Expected: \"%s\", got: \"%s\"", original_str, transposed_twice_str);
    free(original_str);
    free(transposed_twice_str);
    matrix_free(original);
    matrix_free(transposed_twice);
}

int main() {
    test1();
    for (size_t i = 1; i < 10; ++i) {
        for (size_t j = 1; j < 10; ++j) {
            iteration(i, j);
        }
    }
}
