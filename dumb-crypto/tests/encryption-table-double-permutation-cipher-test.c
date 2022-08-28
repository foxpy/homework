#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"
#include "qc.h"

static char const* samples[] = {
        "ПРИЛЕТАЮСЕДЬМОГО",
        "ВЫЛЕТАЮДЕВЯТОГО!",
        "AREYAWINNINGSON?",
};
#define SAMPLES_LENGTH (sizeof(samples)/sizeof(samples[0]))

static size_t const permutations[][4] = {
        {0, 2, 1, 3},
        {1, 2, 0, 3},
        {2, 1, 3, 0},
        {3, 0, 1, 2},
        {0, 1, 3, 2},
        {2, 0, 3, 1},
};
#define PERMUTATIONS_LENGTH (sizeof(permutations)/sizeof(permutations[0]))

static void simple_test() {
    char const* input = "ПРИЛЕТАЮСЕДЬМОГО";
    char* encrypted = encryption_table_double_permutation_encrypt(
            input,
            4, (size_t const[]){3, 0, 2, 1},
            4, (size_t const[]){2, 0, 3, 1}
    );
    qc_assert(strcmp(encrypted, "ТЮАЕООГМРЛИПЕЬДС") == 0,
              "Encryption table double permutation cipher encryption is broken");
    char* decrypted = encryption_table_double_permutation_decrypt(
            encrypted,
            4, (size_t const[]){3, 0, 2, 1},
            4, (size_t const[]){2, 0, 3, 1}
    );
    free(encrypted);
    free(decrypted);
}

static void iteration4x4(char const* input,
                         size_t const horizontal_permutation[static 4],
                         size_t const vertical_permutation[static 4]) {
    char* encrypted = encryption_table_double_permutation_encrypt(
            input,
            4, horizontal_permutation,
            4, vertical_permutation
    );
    char* decrypted = encryption_table_double_permutation_decrypt(
            encrypted,
            4, horizontal_permutation,
            4, vertical_permutation
    );
    qc_assert(strcmp(decrypted, input) == 0,
              "Encryption table double permutation cipher is unreliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 0; i < SAMPLES_LENGTH; ++i) {
        for (size_t j = 0; j < PERMUTATIONS_LENGTH; ++j) {
            for (size_t k = 0; k < PERMUTATIONS_LENGTH; ++k) {
                iteration4x4(samples[i], permutations[j], permutations[k]);
            }
        }
    }
}
