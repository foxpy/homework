#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "crypto.h"
#include "qc.h"
#include "str.h"
#include "unicode.h"

static bool is_magic_square(size_t len, size_t const square[static len]) {
    size_t a = sqrt(len);
    if (a * a != len) {
        return false;
    } else {
        size_t sum, target_sum = 0;
        for (size_t i = 0; i < a; ++i) {
            target_sum += square[i];
        }
        for (size_t i = 0; i < a; ++i) {
            sum = 0;
            for (size_t j = 0; j < a; ++j) {
                sum += square[i*a + j];
            }
            if (sum != target_sum) {
                return false;
            }
        }
        for (size_t i = 0; i < a; ++i) {
            sum = 0;
            for (size_t j = 0; j < a; ++j) {
                sum += square[j*a + i];
            }
            if (sum != target_sum) {
                return false;
            }
        }
        sum = 0;
        for (size_t i = 0; i < a; ++i) {
            sum += square[i*a + i];
        }
        if (sum != target_sum) {
            return false;
        }
        return true;
    }
}

static size_t to_index(size_t len, size_t const square[static len], size_t num) {
    for (size_t i = 0; i < len; ++i) {
        if (square[i] == num) {
            return i;
        }
    }
    UNREACHABLE_CODE();
}

char* magic_square_encrypt(char const* input_str, size_t len, size_t const square[static len]) {
    assert(input_str != NULL);
    if(!is_magic_square(len, square)) {
        return NULL;
    }
    str* encrypted = str_new();
    char const** mat = emalloc(len * sizeof(char const*));
    size_t i = 0, j = 1, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        if (j > len) {
            j = 1;
            for (size_t k = 0; k < len; ++k) {
                str_push_unicode_character_back(encrypted, mat[k]);
            }
        }
        mat[to_index(len, square, j)] = &input_str[i];
        ++j;
        i += symbol_length;
    }
    free(mat);
    return str_to_c(encrypted);
}

char* magic_square_decrypt(char const* input_str, size_t len, size_t const square[static len]) {
    assert(input_str != NULL);
    assert(is_magic_square(len, square));
    str* decrypted = str_new();
    char const** mat = emalloc(len * sizeof(char const*));
    size_t mat_fill = 0;
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        if (mat_fill == len) {
            mat_fill = 0;
            for (size_t j = 1; j <= len; ++j) {
                str_push_unicode_character_back(decrypted, mat[to_index(len, square, j)]);
            }
        }
        mat[mat_fill] = &input_str[i];
        ++mat_fill;
        i += symbol_length;
    }
    free(mat);
    return str_to_c(decrypted);
}
