#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>
#include "ecc-exists.h"

void verbose_print(bool verbose, const char* format, ...) {
    if (verbose) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

static double factorial(size_t n) {
    double sum = 1;
    for (size_t i = 1; i <= n; ++i) {
        sum *= i;
    }
    return sum;
}

static double C(size_t n, size_t k) {
    return factorial(n)/(factorial(k) * factorial(n - k));
}

double volume(size_t q, size_t e, size_t n) {
    double sum = 0;
    for (size_t i = 0; i <= e; ++i) {
        sum += C(n, i) * pow((double) (q - 1), i);
    }
    return sum;
}

size_t e(size_t d) {
    return (d - 1) / 2;
}
