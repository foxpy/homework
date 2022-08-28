#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "str.h"
#include "crypto.h"
#include "qc.h"
#include "unicode.h"

static char const** mat_shuffle(char const** mat, size_t x, size_t y) {
    char const** tmp = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            tmp[x*j + i] = mat[y*i + j];
        }
    }
    free(mat);
    return tmp;
}

static char const** mat_deshuffle(char const** mat, size_t x, size_t y) {
    char const** tmp = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            tmp[y*i + j] = mat[x*j + i];
        }
    }
    free(mat);
    return tmp;
}

char* encryption_table_impl(const char* input_str, size_t x, size_t y, bool encrypt) {
    str* encrypted = str_new();
    char const** mat = emalloc(x * y * sizeof(char const*));
    size_t mat_fill = 0;
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        if (mat_fill == x * y) {
            mat_fill = 0;
            if (encrypt) {
                mat = mat_shuffle(mat, x, y);
            } else {
                mat = mat_deshuffle(mat, x, y);
            }
            for (size_t j = 0; j < x * y; ++j) {
                str_push_unicode_character_back(encrypted, mat[j]);
            }
        }
        mat[mat_fill] = &input_str[i];
        ++mat_fill;
        i += symbol_length;
    }
    free(mat);
    return str_to_c(encrypted);
}

char* encryption_table_encrypt(char const* input_str, size_t x, size_t y) {
    assert(input_str != NULL);
    assert(x > 0 && y > 0);
    return encryption_table_impl(input_str, x, y, true);
}

char* encryption_table_decrypt(char const* input_str, size_t x, size_t y) {
    assert(input_str != NULL);
    assert(x > 0 && y > 0);
    return encryption_table_impl(input_str, x, y, false);
}
