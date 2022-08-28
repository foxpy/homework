#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "crypto.h"
#include "qc.h"

static char const* samples[] = {
        "COMPRESSION",
        "LOREMIPSUM"
};
#define SAMPLES_LENGTH (sizeof(samples)/sizeof(samples[0]))

static void simple_test() {
    char const* input = "WAR";
    char* encrypted = polybius_square_encrypt(input);
    qc_assert(strcmp(encrypted, "52 11 42") == 0,
              "Polybius square cipher encryption is broken");
    char* decrypted = polybius_square_decrypt(encrypted);
    qc_assert(strcmp(decrypted, input) == 0,
              "Polybius square cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

static void iteration(char const* input) {
    char* encrypted = polybius_square_encrypt(input);
    char* decrypted = polybius_square_decrypt(encrypted);
    qc_assert(strcmp(input, decrypted) == 0, "Polybius square cipher is broken");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 0; i < SAMPLES_LENGTH; ++i) {
        iteration(samples[i]);
    }
}
