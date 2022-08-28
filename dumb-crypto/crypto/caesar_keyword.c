#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "crypto.h"
#include "qc.h"
#include "unicode.h"
#include "str.h"

static char const* alphabet[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И",
        "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т",
        "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь",
        "Э", "Ю", "Я"
};
#define ALPHABET_LENGTH (sizeof(alphabet)/sizeof(alphabet[0]))

typedef struct lookup_table {
    char const* from;
    char const* to;
} lookup_table;

static lookup_table* generate_table(size_t k, char const* key) {
    lookup_table* table = emalloc(ALPHABET_LENGTH * sizeof(lookup_table));
    memset(table, 0, ALPHABET_LENGTH * sizeof(lookup_table));
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        table[i].from = alphabet[i];
    }
    {
        size_t i = 0, end = strlen(key);
        while (i < end) {
            size_t symbol_length = unicode_symbol_len(&key[i]);
            bool already_exists = false;
            for (size_t j = 0; j < ALPHABET_LENGTH; ++j) {
                if (table[j].to != NULL && strncmp(table[j].to, &key[i], symbol_length) == 0) {
                    already_exists = true;
                }
            }
            if (!already_exists) {
                table[k].to = &key[i];
                k = (k + 1) % ALPHABET_LENGTH;
            }
            i += symbol_length;
        }
    }
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        bool already_exists = false;
        for (size_t j = 0; j < ALPHABET_LENGTH; ++j) {
            if (table[j].to != NULL && strncmp(table[j].to, alphabet[i], strlen(alphabet[i])) == 0) {
                already_exists = true;
            }
        }
        if (!already_exists) {
            table[k].to = alphabet[i];
            k = (k + 1) % ALPHABET_LENGTH;
        }
    }
    return table;
}

char* caesar_keyword_cipher_encrypt(const char* input_str, size_t k, char const* key) {
    assert(k < ALPHABET_LENGTH);
    str* encrypted = str_new();
    lookup_table* table = generate_table(k, key);
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        for (size_t j = 0; j < ALPHABET_LENGTH; ++j) {
            if (strncmp(table[j].from, &input_str[i], symbol_length) == 0) {
                str_push_unicode_character_back(encrypted, table[j].to);
            }
        }
        i += symbol_length;
    }
    free(table);
    return str_to_c(encrypted);
}

char* caesar_keyword_cipher_decrypt(const char* input_str, size_t k, char const* key) {
    assert(k < ALPHABET_LENGTH);
    str* decrypted = str_new();
    lookup_table* table = generate_table(k, key);
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        for (size_t j = 0; j < ALPHABET_LENGTH; ++j) {
            if (strncmp(table[j].to, &input_str[i], symbol_length) == 0) {
                str_push_unicode_character_back(decrypted, table[j].from);
            }
        }
        i += symbol_length;
    }
    free(table);
    return str_to_c(decrypted);
}
