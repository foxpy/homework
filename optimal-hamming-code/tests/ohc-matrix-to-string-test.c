#include <string.h>
#include <qc.h>
#include "matrix.h"

int main() {
    bit** mat = matrix_new(3, 4);
    mat[0][0] = 0; mat[0][1] = 0; mat[0][2] = 1; mat[0][3] = 0;
    mat[1][0] = 1; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = 0;
    mat[2][0] = 0; mat[2][1] = 1; mat[2][2] = 0; mat[2][3] = 1;
    char const* expected = "0 0 1 0\n1 1 0 0\n0 1 0 1\n";
    char* formatted = matrix_to_string(mat);
    qc_assert(strcmp(formatted, expected) == 0, "Expected: %s, got: %s", expected, formatted);
    free(formatted);
    matrix_free(mat);
}
