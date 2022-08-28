#include <string.h>
#include "crypto.h"
#include "qc.h"
#include "unicode.h"

static char const* inputs[] = {
        "ПРИЛЕТАЮСЕДЬМОГОВПОЛДЕНЬ",
        "Sed ut perspiciatis, unde omnis",
        "iste natus error sit voluptatem",
        "нет никого, кто возлюбил бы",
        "предпочел и возжаждал бы",
        "само страдание только за то",
        "Этот шифр мне тоже не нравится"
};
#define INPUTS_LENGTH (sizeof(inputs)/sizeof(inputs[0]))

static char const* keys[] = {
        "КОРОВА",
        "ВРАЧ",
        "ТЕЛО",
        "ЗВЕЗДА",
        "РАБОТА"
};
#define KEYS_LENGTH (sizeof(keys)/sizeof(keys[0]))

static void simple_test() {
    char const* input = inputs[0];
    char* encrypted = encryption_table_single_permutation_encrypt(input, keys[0], 4);
    qc_assert(strcmp(encrypted, "ДВПЕМСЕПРТОЕНОИАГДЬЛЛЮОЬ") == 0,
              "Encryption table single permutation cipher encryption is broken");
    char* decrypted = encryption_table_single_permutation_decrypt(encrypted, keys[0], 4);
    qc_assert(strcmp(decrypted, input) == 0,
              "Encryption table signle permutation decryption is broken");
    free(encrypted);
    free(decrypted);
}

static void iteration(char const* input, char const* key, size_t y) {
    char* encrypted = encryption_table_single_permutation_encrypt(input, key, y);
    char* decrypted = encryption_table_single_permutation_decrypt(encrypted, key, y);
    qc_assert(strncmp(input, decrypted, y * unicode_characters(key)) == 0,
              "Encryption table single permutation is unreliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 0; i < INPUTS_LENGTH; ++i) {
        for (size_t j = 0; j < KEYS_LENGTH; ++j) {
            for (size_t k = 1; k < 5; ++k) {
                iteration(inputs[i], keys[j], k);
            }
        }
    }
}
