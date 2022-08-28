#include <stdbool.h>
#include <qc.h>
#include "matrix.h"

static bit** populate_matrix_A() {
    bit** A = matrix_new(3, 4);
    A[0][0] = 0;
    A[0][1] = 0;
    A[0][2] = 1;
    A[0][3] = 0;
    A[1][0] = 1;
    A[1][1] = 0;
    A[1][2] = 0;
    A[1][3] = 1;
    A[2][0] = 0;
    A[2][1] = 1;
    A[2][2] = 0;
    A[2][3] = 1;
    return A;
}

static bit** populate_matrix_B() {
    bit** B = matrix_new(4, 2);
    B[0][0] = 1;
    B[0][1] = 1;
    B[1][0] = 0;
    B[1][1] = 1;
    B[2][0] = 0;
    B[2][1] = 0;
    B[3][0] = 1;
    B[3][1] = 0;
    return B;
}

static bool check_matrix_C(bit *const* C) {
    qc_assert(MATRIX_SIZE_M(C) == 3 && MATRIX_SIZE_N(C) == 2,
                     "Expected matrix size 3 x 2, got %zu x %zu", MATRIX_SIZE_M(C), MATRIX_SIZE_N(C));
    char* fail_message;
    qc_asprintf(&fail_message, "Expected matrix 0,0,0,1,1,1, got matrix %c,%c,%c,%c,%c,%c",
                 C[0][0] ? '1' : '0', C[0][1] ? '1' : '0',
                 C[1][0] ? '1' : '0', C[1][1] ? '1' : '0',
                 C[2][0] ? '1' : '0', C[2][1] ? '1' : '0');
    qc_assert(C[0][0] == 0 && C[0][1] == 0 &&
              C[1][0] == 0 && C[1][1] == 1 &&
              C[2][0] == 1 && C[2][1] == 1,
              "%s", fail_message);
    free(fail_message);
    return false;
}

int main() {
    bit** A = populate_matrix_A();
    bit** B = populate_matrix_B();
    bit** C = matrix_multiply(A, B);
    check_matrix_C(C);
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
}
