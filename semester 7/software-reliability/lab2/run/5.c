#include <stdio.h>
#include "5.h"

int main() {
    size_t numerator, denominator;
    lab5(&numerator, &denominator);
    printf("%zu / %zu\n", numerator, denominator);
}
