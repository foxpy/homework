#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "crypto.h"
#include "unicode.h"
#include "qc.h"
#include "str.h"

static char const* alphabet[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И",
        "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т",
        "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь",
        "Э", "Ю", "Я",
};
#define ALPHABET_LENGTH (sizeof(alphabet)/sizeof(alphabet[0]))

static ptrdiff_t ord(size_t len, const char symbol[static len]) {
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        if (strncmp(alphabet[i], symbol, len) == 0) {
            return i;
        }
    }
    return -1;
}

static ptrdiff_t reverse_ord(size_t len, const char symbol[static len], size_t a, size_t b) {
    for (size_t i = 0; i < ALPHABET_LENGTH; ++i) {
        if (strncmp(alphabet[(a * i + b) % ALPHABET_LENGTH], symbol, len) == 0) {
            return i;
        }
    }
    return -1;
}

static char* affine_caesar_cipher_impl(const char* input_str, size_t a, size_t b, bool encrypt) {
    assert(input_str != NULL);
    str* ret = str_new();
    if (a > ALPHABET_LENGTH || b > ALPHABET_LENGTH || gcd(a, ALPHABET_LENGTH) != 1) {
        return NULL;
    }
    size_t i = 0, end = strlen(input_str);
    while (i <= end) {
        size_t symbol_length = unicode_symbol_len(&input_str[i]);
        ptrdiff_t index = ord(symbol_length, &input_str[i]);
        if (index != -1) {
            if (encrypt) {
                str_push_back(ret, alphabet[(a * index + b) % ALPHABET_LENGTH]);
            } else {
                ptrdiff_t original_index = reverse_ord(symbol_length, &input_str[i], a, b);
                if (original_index != -1) {
                    str_push_back(ret, alphabet[original_index]);
                }
            }
        }
        i += symbol_length;
    }
    return str_to_c(ret);
}

char* affine_caesar_cipher_encrypt(char const* input_str, size_t a, size_t b) {
    return affine_caesar_cipher_impl(input_str, a, b, true);
}

char* affine_caesar_cipher_decrypt(char const* input_str, size_t a, size_t b) {
    return affine_caesar_cipher_impl(input_str, a, b, false);
}
