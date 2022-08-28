#include <string.h>
#include <qc.h>
#include "matrix.h"

int main() {
    size_t const expected_permutation[] = {0, 4, 1, 3, 2};
    bit** mat = matrix_new(3, 5);
    mat[0][0] = 1; mat[0][1] = 1; mat[0][2] = 0; mat[0][3] = 0; mat[0][4] = 1;
    mat[1][0] = 1; mat[1][1] = 0; mat[1][2] = 0; mat[1][3] = 1; mat[1][4] = 0;
    mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = 0; mat[2][4] = 1;
    size_t* permutation = matrix_to_systematic(mat);
    char const* expected_str = "1 1 1 0 0\n1 0 0 1 0\n0 1 0 0 1\n";
    char* matrix_str = matrix_to_string(mat);
    qc_assert(strcmp(matrix_str, expected_str) == 0,
                     "Expected: \"%s\", got: \"%s\"", expected_str, matrix_str);
    qc_assert(memcmp(expected_permutation, permutation, sizeof(expected_permutation)) == 0,
              "matrix_to_systematic returns invalid permutation");
    free(matrix_str);
    free(permutation);
    matrix_free(mat);
}
