#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include "crypto.h"
#include "str.h"
#include "unicode.h"

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

char* polybius_square_v2_encrypt(char const* input_str) {
    str* encrypted = str_new();
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t index = table_lookup(symbol_length, &input_str[i]);
        if (index != -1) {
            index += TABLE_DIM;
            index %= TABLE_LENGTH;
            str_push_back(encrypted, table[index]);
        }
        i += symbol_length;
    }
    return str_to_c(encrypted);
}

char* polybius_square_v2_decrypt(char const* input_str) {
    str* decrypted = str_new();
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t index = table_lookup(symbol_length, &input_str[i]);
        if (index != -1) {
            index += TABLE_LENGTH;
            index -= TABLE_DIM;
            index %= TABLE_LENGTH;
            str_push_back(decrypted, table[index]);
        }
        i += symbol_length;
    }
    return str_to_c(decrypted);
}
