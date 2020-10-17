#include <stdio.h>
#include <stddef.h>
#include <qc.h>
#include "5.h"

void lab5(size_t* numerator, size_t* denominator) {
    scanf("%zu %zu", numerator, denominator);
    size_t divider = gcd(*numerator, *denominator);
    *numerator /= divider;
    *denominator /= divider;
}
