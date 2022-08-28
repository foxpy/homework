#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "crypto.h"
#include "qc.h"
#include "unicode.h"
#include "str.h"

static char const* alphabet[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Й",
        "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У",
        "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э",
        "Ю", "Я"
};
#define ALPHABET_LENGTH (sizeof(alphabet)/sizeof(alphabet[0]))

static ptrdiff_t table_lookup(size_t len, char const* table[static len], char const* symbol) {
    for (size_t i = 0; i < len; ++i) {
        if (table[i] != NULL && strncmp(table[i], symbol, unicode_symbol_len(symbol)) == 0) {
            return i;
        }
    }
    return -1;
}

static char const** create_table(size_t x, size_t y, char const* key) {
    char const** mat = emalloc(x * y * sizeof(char const*));
    for (size_t i = 0; i < x * y; ++i) {
        mat[i] = NULL;
    }
    size_t mat_fill = 0;
    {
        size_t i = 0, end = strlen(key);
        while (i < end) {
            size_t symbol_length = unicode_symbol_len(&key[i]);
            if (table_lookup(x * y, mat, &key[i]) == -1) {
                mat[mat_fill] = &key[i];
                ++mat_fill;
            }
            i += symbol_length;
        }
    }
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        if (table_lookup(x * y, mat, alphabet[i]) == -1) {
            mat[mat_fill] = alphabet[i];
            ++mat_fill;
        }
    }
    assert(mat_fill == x * y);
    return mat;
}

char* trithemius_cipher_encrypt(char const* input_str, size_t x, size_t y, char const* key) {
    str* encrypted = str_new();
    char const** table = create_table(x, y, key);
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t plaintext_index = table_lookup(x * y, table, &input_str[i]);
        if (plaintext_index != -1) {
            size_t ciphertext_index = (plaintext_index + x) % (x * y);
            str_push_unicode_character_back(encrypted, table[ciphertext_index]);
        }
        i += symbol_length;
    }
    free(table);
    return str_to_c(encrypted);
}

char* trithemius_cipher_decrypt(char const* input_str, size_t x, size_t y, char const* key) {
    str* decrypted = str_new();
    char const** table = create_table(x, y, key);
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t ciphertext_index = table_lookup(x * y, table, &input_str[i]);
        if (ciphertext_index != -1) {
            size_t plaintext_index = (ciphertext_index + (x * y) - x) % (x * y);
            str_push_unicode_character_back(decrypted, table[plaintext_index]);
        }
        i += symbol_length;
    }
    free(table);
    return str_to_c(decrypted);
}
