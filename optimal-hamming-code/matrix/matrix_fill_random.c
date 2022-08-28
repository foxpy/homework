#include <qc.h>
#include "matrix.h"

void matrix_fill_random(bit** matrix) {
    qc_rnd rnd;
    qc_rnd_init(&rnd, NULL);
    for (size_t i = 0; i < MATRIX_SIZE_M(matrix); ++i) {
        for (size_t j = 0; j < MATRIX_SIZE_N(matrix); ++j) {
            matrix[i][j] = qc_rnd64(&rnd) % 2;
        }
    }
}

