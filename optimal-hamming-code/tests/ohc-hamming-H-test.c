#include <string.h>
#include <qc.h>
#include "hamming.h"
#include "matrix.h"

static void compare_matrix(bit *const* matrix, char const* str) {
    char* actual_value = matrix_to_string(matrix);
    qc_assert(strcmp(actual_value, str) == 0, "Expected: \"%s\", got: \"%s\"", str, actual_value);
    free(actual_value);
}

int main() {
    {
        bit **H = hamming_H(3, 1);
        compare_matrix(H,
                       "0 1 1\n"
                       "1 0 1\n");
        matrix_free(H);
    }
    {
        bit **H = hamming_H(7, 4);
        compare_matrix(H,
                       "0 0 0 1 1 1 1\n"
                       "0 1 1 0 0 1 1\n"
                       "1 0 1 0 1 0 1\n");
        matrix_free(H);
    }
    {
        bit **H = hamming_H(5, 2);
        compare_matrix(H,
                       "0 0 0 1 1\n"
                       "0 1 1 0 0\n"
                       "1 0 1 0 1\n");
        matrix_free(H);
    }
}
