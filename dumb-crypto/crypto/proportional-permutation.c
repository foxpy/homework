#include <string.h>
#include <stddef.h>
#include "crypto.h"
#include "str.h"
#include "unicode.h"

static char const* table[] = {
        " ", "О", "Е", "А", "И", "Т", "Н", "С", "Р", "В", "Л", "К", "М", "Д", "П", "У",
        "Я", "Ы", "З", "Ъ", "Б", "Г", "Ч", "Й", "Х", "Ж", "Ю", "Ш", "Ц", "Щ", "Э", "Ф"
};
#define TABLE_LENGTH (sizeof(table)/sizeof(table[0]))

static ptrdiff_t table_lookup(size_t len, char const symbol[len]) {
    if (strncmp("Ь", symbol, len) == 0) {
        return table_lookup(sizeof("Ъ"), "Ъ");
    }
    for (size_t i = 0; i < TABLE_LENGTH; ++i) {
        if (strncmp(table[i], symbol, len) == 0) {
            return i;
        }
    }
    return -1;
}

char* proportional_permutation_impl(char const* input_str) {
    str* processed = str_new();
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t index = table_lookup(symbol_length, &input_str[i]);
        if (index != -1) {
            index = (2*TABLE_LENGTH - index - 1) % TABLE_LENGTH;
            str_push_back(processed, table[index]);
        }
        i += symbol_length;
    }
    return str_to_c(processed);
}

char* proportional_permutation_encrypt(char const* input_str) {
    return proportional_permutation_impl(input_str);
}

char* proportional_permutation_decrypt(char const* input_str) {
    return proportional_permutation_impl(input_str);
}
