#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include "crypto.h"
#include "str.h"
#include "unicode.h"
#include "qc.h"

static char const* alphabet[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И",
        "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т",
        "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь",
        "Э", "Ю", "Я",
};
#define ALPHABET_LENGTH (sizeof(alphabet)/sizeof(alphabet[0]))

static size_t* key_to_permutation(char const* key) {
    size_t table_size = unicode_characters(key);
    size_t* ret = emalloc(table_size * sizeof(size_t));
    size_t counter = 0;
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        size_t j = 0, end = strlen(key);
        size_t table_index = 0;
        while (j < end) {
            size_t symbol_length = unicode_symbol_len(&key[j]);
            if (strncmp(alphabet[i], &key[j], unicode_symbol_len(alphabet[i])) == 0) {
                ret[table_index] = counter;
                ++counter;
            }
            ++table_index;
            j += symbol_length;
        }
    }
    return ret;
}

static char const** table_transpose(size_t x, size_t y, char const* table[static x * y]) {
    char const** new_table = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            new_table[j*x + i] = table[i*y + j];
        }
    }
    free(table);
    return new_table;
}

static char const** table_detranspose(size_t x, size_t y, char const* table[static x * y]) {
    char const** new_table = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            new_table[i*y + j] = table[j*x + i];
        }
    }
    free(table);
    return new_table;
}

static char const** table_encrypt(size_t x, size_t y, char const* table[static x * y], size_t const permutation[static x]) {
    char const** new_table = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            new_table[permutation[i]*y + j] = table[i*y + j];
        }
    }
    free(table);
    new_table = table_transpose(x, y, new_table);
    return new_table;
}

static char const** table_decrypt(size_t x, size_t y, char const* table[static x * y], size_t const permutation[static x]) {
    table = table_detranspose(x, y, table);
    char const** new_table = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            new_table[i*y + j] = table[permutation[i]*y + j];
        }
    }
    free(table);
    return new_table;
}

char* encryption_table_single_permutation_impl(char const* input_str, char const* key, size_t y, bool encrypt) {
    str* encrypted = str_new();
    size_t x = unicode_characters(key);
    size_t table_fill = 0, table_size = x * y;
    char const** table = emalloc(table_size * sizeof(char const**));
    size_t* permutation = key_to_permutation(key);
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        table[table_fill] = &input_str[i];
        ++table_fill;
        if (table_fill == table_size) {
            if (encrypt) {
                table = table_encrypt(x, y, table, permutation);
            } else {
                table = table_decrypt(x, y, table, permutation);
            }
            for (size_t j = 0; j < table_size; ++j) {
                str_push_unicode_character_back(encrypted, table[j]);
            }
            table_fill = 0;
        }
        i += symbol_length;
    }
    free(permutation);
    free(table);
    return str_to_c(encrypted);
}

char* encryption_table_single_permutation_encrypt(char const* input_str, char const* key, size_t y) {
    return encryption_table_single_permutation_impl(input_str, key, y, true);
}

char* encryption_table_single_permutation_decrypt(char const* input_str, char const* key, size_t y) {
    return encryption_table_single_permutation_impl(input_str, key, y, false);
}
