#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include "ecc-exists.h"

enum estimation gilbert_varshamov_bound(size_t q, size_t n, size_t k, size_t d, bool verbose) {
    if (pow(q, (double) (k - 1)) * volume(q, 2 * e(d), n) < pow(q, n)) {
        verbose_print(verbose, "Code exists by Gilbert-Varshamov bound\n");
        return CODE_EXISTS;
    } else {
        verbose_print(verbose, "Code does not exist by Gilbert-Varshamov bound\n");
        return CODE_PROBABLY_EXISTS;
    }
}
