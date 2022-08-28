#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "crypto.h"
#include "qc.h"

static char const* samples[] = {
        "УРРРА ЙА ПИДОРАС ЭГЕЕЕЙ",
        "ЯЙЙЙЦФРЦФЫШЗЭЙЦХФОЛЩЩЩР",
        "ОБОЖАЮ СВОЕГО ПРЕПОДА",
        "ТОЧНО НЕ САРКАЗМ",
        "НЕ НЕ НЕ НЕ"
};
#define SAMPLES_LENGTH (sizeof(samples)/sizeof(samples[0]))

static void simple_test() {
    char* encrypted = proportional_permutation_encrypt(samples[0]);
    qc_assert(strcmp(encrypted, samples[1]) == 0,
              "Proportional permutation cipher encryption is broken");
    char* decrypted = proportional_permutation_decrypt(encrypted);
    qc_assert(strcmp(decrypted, samples[0]) == 0,
              "Proportional permutation cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

static void iteration(char const* input) {
    char* encrypted = proportional_permutation_encrypt(input);
    char* decrypted = proportional_permutation_decrypt(encrypted);
    qc_assert(strcmp(input, decrypted) == 0, "Proportional permutation cipher is unreliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 0; i < SAMPLES_LENGTH; ++i) {
        iteration(samples[i]);
    }
}
