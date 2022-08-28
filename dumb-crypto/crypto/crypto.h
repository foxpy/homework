#pragma once
#include <stddef.h>

char* encryption_table_encrypt(char const* input_str, size_t x, size_t y);
char* encryption_table_decrypt(char const* input_str, size_t x, size_t y);

char* encryption_table_single_permutation_encrypt(char const* input_str, char const* key, size_t y);
char* encryption_table_single_permutation_decrypt(char const* input_str, char const* key, size_t y);

char* encryption_table_double_permutation_encrypt(
        char const* input_str,
        size_t x, size_t const* horizontal_permutation,
        size_t y, size_t const* vertical_permutation
);
char* encryption_table_double_permutation_decrypt(
        char const* input_str,
        size_t x, size_t const* horizontal_permutation,
        size_t y, size_t const* vertical_permutation
);

char* caesar_cipher_encrypt(char const* input_str, size_t key);
char* caesar_cipher_decrypt(char const* input_str, size_t key);

char* affine_caesar_cipher_encrypt(char const* input_str, size_t a, size_t b);
char* affine_caesar_cipher_decrypt(char const* input_str, size_t a, size_t b);

char* caesar_keyword_cipher_encrypt(const char* input_str, size_t k, char const* key);
char* caesar_keyword_cipher_decrypt(const char* input_str, size_t k, char const* key);

char* magic_square_encrypt(char const* input_str, size_t len, size_t const* square);
char* magic_square_decrypt(char const* input_str, size_t len, size_t const* square);

char* trithemius_cipher_encrypt(char const* input_str, size_t x, size_t y, char const* key);
char* trithemius_cipher_decrypt(char const* input_str, size_t x, size_t y, char const* key);

char* playfair_cipher_encrypt(char const* input_str, size_t x, size_t y, char const* key);
char* playfair_cipher_decrypt(char const* input_str, size_t x, size_t y, char const* key);

char* vigenere_cipher_encrypt(char const* input_str, char const* key);
char* vigenere_cipher_decrypt(char const* input_str, char const* key);

char* wheatstone_two_square_encrypt(char const* input_str);
char* wheatstone_two_square_decrypt(char const* input_str);

char* polybius_square_encrypt(char const* input_str);
char* polybius_square_decrypt(char const* input_str);

char* polybius_square_v2_encrypt(char const* input_str);
char* polybius_square_v2_decrypt(char const* input_str);

char* proportional_permutation_encrypt(char const* input_str);
char* proportional_permutation_decrypt(char const* input_str);
