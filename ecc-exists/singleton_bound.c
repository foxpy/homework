#include <stddef.h>
#include <stdbool.h>
#include "ecc-exists.h"

enum estimation singleton_bound(size_t q, size_t n, size_t k, size_t d, bool verbose) {
    if (q != 2) {
        verbose_print(verbose, "Singleton bound does not apply to codes with q != 2\n");
        return CODE_PROBABLY_EXISTS;
    } else {
        if (d <= (n - k + 1)) {
            verbose_print(verbose, "Code exists by Singleton bound\n");
            return CODE_PROBABLY_EXISTS;
        } else {
            verbose_print(verbose, "Code does not exist by Singleton bound\n");
            return CODE_DOES_NOT_EXIST;
        }
    }
}
