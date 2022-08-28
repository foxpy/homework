#include <stddef.h>
#include <qc.h>
#include "hamming.h"

static void check(size_t expected_n, size_t k) {
    size_t actual_n = hamming_n(k);
    qc_assert(expected_n == actual_n, "Expected: %zu, got: %zu", expected_n, actual_n);
}

int main() {
    check(3, 1);
    check(5, 2);
    check(6, 3);
    check(7, 4);
    check(9, 5);
    check(10, 6);
    check(11, 7);
    check(12, 8);
    check(13, 9);
    check(14, 10);
    check(15, 11);
}
