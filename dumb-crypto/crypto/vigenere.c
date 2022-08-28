#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "crypto.h"
#include "str.h"
#include "qc.h"
#include "unicode.h"

static char const* alphabet[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Й",
        "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У",
        "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э",
        "Ю", "Я"
};
#define ALPHABET_LENGTH (sizeof(alphabet)/sizeof(alphabet[0]))

static ptrdiff_t alphabet_index(char const* symbol) {
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        if (strncmp(alphabet[i], symbol, unicode_symbol_len(symbol)) == 0) {
            return i;
        }
    }
    return -1;
}

static const char** generate_table() {
    char const** table = emalloc(ALPHABET_LENGTH * ALPHABET_LENGTH * sizeof(char const**));
    for (size_t y = 0; y < ALPHABET_LENGTH; ++y) {
        for (size_t x = 0; x < ALPHABET_LENGTH; ++x) {
            table[y * ALPHABET_LENGTH + x] = alphabet[(x + y) % ALPHABET_LENGTH];
        }
    }
    return table;
}

char* vigenere_cipher_encrypt(char const* input_str, char const* key) {
    str* encrypted = str_new();
    char const** table = generate_table();
    size_t key_counter = 0, key_length = strlen(key);
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        ptrdiff_t x = alphabet_index(&input_str[i]);
        ptrdiff_t y = alphabet_index(&key[key_counter]);
        assert(x >= 0 && y >= 0);
        str_push_back(encrypted, table[y * ALPHABET_LENGTH + x]);
        i += unicode_symbol_len(&input_str[i]);
        key_counter = (key_counter + unicode_symbol_len(&key[key_counter])) % key_length;
    }
    free(table);
    return str_to_c(encrypted);
}

char* vigenere_cipher_decrypt(char const* input_str, char const* key) {
    str* decrypted = str_new();
    char const** table = generate_table();
    size_t key_counter = 0, key_length = strlen(key);
    size_t i = 0, end = strlen(input_str);
    while (i < end) {
        ptrdiff_t x = alphabet_index(&input_str[i]);
        ptrdiff_t y = alphabet_index(&key[key_counter]);
        assert(x >= 0 && y >= 0);
        for (size_t j = 0; j < ALPHABET_LENGTH; ++j) {
            if (strncmp(table[y * ALPHABET_LENGTH + j], &input_str[i], unicode_symbol_len(&input_str[i])) == 0) {
                str_push_back(decrypted, alphabet[j]);
                break;
            }
        }
        i += unicode_symbol_len(&input_str[i]);
        key_counter = (key_counter + unicode_symbol_len(&key[key_counter])) % key_length;
    }
    free(table);
    return str_to_c(decrypted);
}
