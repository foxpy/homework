#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <qc.h>
#include "matrix.h"

bit** matrix_new(size_t m, size_t n) {
    assert(m != 0 && n != 0);
    size_t* mem = qc_malloc(m * sizeof(bit*) + 2 * sizeof(size_t));
    mem[0] = m;
    mem[1] = n;
    bit** ret = (bit**) &mem[2];
    for (size_t i = 0; i < m; ++i) {
        ret[i] = qc_malloc(n * sizeof(bit));
        memset(ret[i], 0, n * sizeof(bit));
    }
    return ret;
}
