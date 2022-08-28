#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include "crypto.h"
#include "str.h"
#include "unicode.h"
#include "qc.h"

static char const* table[] = {
        "A", "B", "C", "D", "E",
        "F", "G", "H", "I", "K",
        "L", "M", "N", "O", "P",
        "Q", "R", "S", "T", "U",
        "V", "W", "X", "Y", "Z"
};
#define TABLE_DIM 5
#define TABLE_LENGTH (sizeof(table)/sizeof(table[0]))

static ptrdiff_t table_lookup(size_t len, char const symbol[len]) {
    for (size_t i = 0; i < TABLE_LENGTH; ++i) {
        if (strncmp(table[i], symbol, len) == 0) {
            return i;
        }
    }
    if (strncmp("J", symbol, len) == 0) {
        return table_lookup(strlen("I"), "I");
    } else {
        return -1;
    }
}

static size_t ctoi(char c) {
    return c - '0';
}

char* polybius_square_encrypt(char const* input_str) {
    str* encrypted = str_new();
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t index = table_lookup(symbol_length, &input_str[i]);
        if (index != -1) {
            size_t x = (index % TABLE_DIM) + 1;
            size_t y = (index / TABLE_DIM) + 1;
            char* buf = sprintf_alloc("%zu%zu ", y, x);
            str_push_back(encrypted, buf);
            free(buf);
        }
        i += symbol_length;
    }
    char* ret = str_to_c(encrypted);
    ret[strlen(ret) - 1] = '\0';
    return ret;
}

char* polybius_square_decrypt(char const* input_str) {
    str* decrypted = str_new();
    size_t i = 0, end = strlen(input_str);
    size_t y = 0, x = 0;
    while (i <= end) {
        if (isdigit(input_str[i])) {
            if (y == 0) {
                y = ctoi(input_str[i]);
            } else {
                x = ctoi(input_str[i]);
                --y;
                --x;
                size_t index = y * TABLE_DIM + x;
                str_push_back(decrypted, table[index]);
                y = 0;
            }
        }
        ++i;
    }
    return str_to_c(decrypted);
}
