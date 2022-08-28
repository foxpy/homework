#include "crypto.h"
#include "unicode.h"
#include "str.h"
#include <stddef.h>
#include <string.h>
#include <assert.h>

static char const* shift_table[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И",
        "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т",
        "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь",
        "Э", "Ю", "Я",
};
#define ALPHABET_LENGTH (sizeof(shift_table)/sizeof(shift_table[0]))

static ptrdiff_t ord(size_t len, const char symbol[static len]) {
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        if (strncmp(shift_table[i], symbol, len) == 0) {
            return i;
        }
    }
    return -1;
}

static char const* chr(size_t index) {
    return shift_table[index % ALPHABET_LENGTH];
}

static char* caesar_cipher_impl(const char* input_str, size_t shift) {
    str* encrypted = str_new();
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t index = ord(symbol_length, &input_str[i]);
        if (index != -1) {
            str_push_back(encrypted, chr(index + shift));
        }
        i += symbol_length;
    }
    return str_to_c(encrypted);
}

char* caesar_cipher_encrypt(char const* input_str, size_t key) {
    assert(input_str != NULL);
    if (key >= ALPHABET_LENGTH || key == 0) {
        return NULL;
    } else {
        return caesar_cipher_impl(input_str, key);
    }
}

char* caesar_cipher_decrypt(char const* input_str, size_t key) {
    assert(input_str != NULL);
    if (key >= sizeof(shift_table)/sizeof(shift_table[0]) || key == 0) {
        return NULL;
    } else {
        return caesar_cipher_impl(input_str, ALPHABET_LENGTH - key);
    }
}
