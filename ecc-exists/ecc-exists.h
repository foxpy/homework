#pragma once
#include <stddef.h>
#include <stdbool.h>

enum estimation {
    CODE_EXISTS,
    CODE_DOES_NOT_EXIST,
    CODE_PROBABLY_EXISTS,
};

enum estimation singleton_bound(size_t q, size_t n, size_t k, size_t d, bool verbose);
enum estimation hamming_bound(size_t q, size_t n, size_t k, size_t d, bool verbose);
enum estimation gilbert_bound(size_t q, size_t n, size_t k, size_t d, bool verbose);
enum estimation gilbert_varshamov_bound(size_t q, size_t n, size_t k, size_t d, bool verbose);

typedef enum estimation (*bound_function)(size_t, size_t, size_t, size_t, bool);

void verbose_print(bool verbose, const char* format, ...);
double volume(size_t q, size_t e, size_t n);
size_t e(size_t d);
