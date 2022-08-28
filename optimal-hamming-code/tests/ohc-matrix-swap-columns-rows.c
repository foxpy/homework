#include <stdlib.h>
#include <string.h>
#include <qc.h>
#include "matrix.h"

int main() {
    bit** mat = matrix_new(2, 3);
    mat[0][0] = 0; mat[0][1] = 1; mat[0][2] = 1;
    mat[1][0] = 0; mat[1][1] = 0; mat[1][2] = 1;

    matrix_swap_rows(mat, 0, 1);
    char const* swapped_rows_expected = "0 0 1\n0 1 1\n";
    char* swapped_rows_actual = matrix_to_string(mat);
    qc_assert(strcmp(swapped_rows_expected, swapped_rows_actual) == 0,
                     "Expected: \"%s\", got: \"%s\"", swapped_rows_expected, swapped_rows_actual);
    free(swapped_rows_actual);

    matrix_swap_columns(mat, 0, 2);
    char const* swapped_columns_expected = "1 0 0\n1 1 0\n";
    char* swapped_columns_actual = matrix_to_string(mat);
    qc_assert(strcmp(swapped_columns_expected, swapped_columns_actual) == 0,
                     "Expected: \"%s\", got: \"%s\"", swapped_columns_expected, swapped_columns_actual);
    free(swapped_columns_actual);

    matrix_free(mat);
}
