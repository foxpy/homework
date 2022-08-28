#include <string.h>
#include <qc.h>
#include "matrix.h"
#include "hamming.h"

static void errorless() {
    bit** H = hamming_H(7, 4);
    bit** G = hamming_G(H);
    bit** I = matrix_new(4, 1);
    I[0][0] = 0; I[1][0] = 1; I[2][0] = 0; I[3][0] = 1;
    bit** C = matrix_multiply(G, I);
    char const* C_str_expected = "1\n1\n0\n0\n1\n1\n0\n";
    char* C_str_actual = matrix_to_string(C);
    qc_assert(strcmp(C_str_expected, C_str_actual) == 0,
                     "Expected: \"%s\", got: \"%s\"", C_str_expected, C_str_actual);
    bit** S = matrix_multiply(H, C);
    char const* S_str_expected = "0\n0\n0\n";
    char* S_str_actual = matrix_to_string(S);
    qc_assert(strcmp(S_str_expected, S_str_actual) == 0,
                     "Expected: \"%s\", got: \"%s\"", S_str_expected, S_str_actual);
    free(S_str_actual);
    free(C_str_actual);
    matrix_free(S);
    matrix_free(C);
    matrix_free(I);
    matrix_free(G);
    matrix_free(H);
}

static void error() {
    bit** H = hamming_H(7, 4);
    bit** G = hamming_G(H);
    bit** I = matrix_new(4, 1);
    I[0][0] = 0; I[1][0] = 1; I[2][0] = 0; I[3][0] = 1;
    bit** C = matrix_multiply(G, I);
    C[5][0] = 0; // + error
    bit** S = matrix_multiply(H, C);
    char const* S_str_expected = "1\n1\n0\n";
    char* S_str_actual = matrix_to_string(S);
    qc_assert(strcmp(S_str_expected, S_str_actual) == 0,
                     "Expected: \"%s\", got: \"%s\"", S_str_expected, S_str_actual);
    free(S_str_actual);
    matrix_free(S);
    matrix_free(C);
    matrix_free(I);
    matrix_free(G);
    matrix_free(H);
}

int main() {
    errorless();
    error();
}
