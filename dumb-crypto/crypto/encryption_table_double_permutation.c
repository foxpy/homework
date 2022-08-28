#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "crypto.h"
#include "str.h"
#include "unicode.h"
#include "qc.h"

static char const** table_encrypt(size_t x, size_t y, char const* table[static x * y],
                                  size_t const horizontal_permutation[static x],
                                  size_t const vertical_permutation[static y]
) {
    char const** new_table_hor = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            new_table_hor[i*x + horizontal_permutation[j]] = table[i*x + j];
        }
    }
    char const** new_table_ver = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            new_table_ver[vertical_permutation[j]*x + i] = new_table_hor[j*x + i];
        }
    }
    free(table);
    free(new_table_hor);
    return new_table_ver;
}

static char const** table_decrypt(size_t x, size_t y, char const* table[static x * y],
                                  size_t const horizontal_permutation[static x],
                                  size_t const vertical_permutation[static y]
) {
    char const** new_table_rev_ver = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            new_table_rev_ver[j*x + i] = table[vertical_permutation[j]*x + i];
        }
    }
    char const** new_table_rev_hor = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < y; ++i) {
        for (size_t j = 0; j < x; ++j) {
            new_table_rev_hor[i*x + j] = new_table_rev_ver[i*x + horizontal_permutation[j]];
        }
    }
    free(table);
    free(new_table_rev_ver);
    return new_table_rev_hor;
}

static char* encryption_table_double_permutation_impl(
        char const* input_str,
        size_t x, size_t const horizontal_permutation[static x],
        size_t y, size_t const vertical_permutation[static y],
        bool encrypt
) {
    str* processed = str_new();
    size_t table_fill = 0, table_size = x * y;
    char const** table = emalloc(table_size * sizeof(char const*));
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        table[table_fill] = &input_str[i];
        ++table_fill;
        if (table_fill == table_size) {
            if (encrypt) {
                table = table_encrypt(x, y, table, horizontal_permutation, vertical_permutation);
            } else {
                table = table_decrypt(x, y, table, horizontal_permutation, vertical_permutation);
            }
            for (size_t j = 0; j < table_size; ++j) {
                str_push_unicode_character_back(processed, table[j]);
            }
            table_fill = 0;
        }
        i += symbol_length;
    }
    free(table);
    return str_to_c(processed);
}

char* encryption_table_double_permutation_encrypt(
        char const* input_str,
        size_t x, size_t const horizontal_permutation[static x],
        size_t y, size_t const vertical_permutation[static y]
) {
    return encryption_table_double_permutation_impl(
            input_str,
            x, horizontal_permutation,
            y, vertical_permutation,
            true
    );
}

char* encryption_table_double_permutation_decrypt(
        char const* input_str,
        size_t x, size_t const horizontal_permutation[static x],
        size_t y, size_t const vertical_permutation[static y]
) {
    return encryption_table_double_permutation_impl(
            input_str,
            x, horizontal_permutation,
            y, vertical_permutation,
            false
    );
}
