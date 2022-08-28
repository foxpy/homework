#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "crypto.h"
#include "qc.h"

static char const* samples[] = {
        "ПРИЛЕТАЮ ШЕСТОГО",
        "ЕСЛИ МЕЧТАЕШЬ О РАДУГЕ, ",
        "БУДЬ ГОТОВ К ДОЖДЮ",
        "АБВГДЕ",
        "ЯЮЭЬ",
};
#define SAMPLES_LENGTH (sizeof(samples)/sizeof(samples[0]))

static void simple_test() {
    char const* input = "ПРИЛЕТАЮ ШЕСТОГО";
    char* encrypted = wheatstone_two_square_encrypt(input);
    qc_assert(strcmp(encrypted, "ПЕОВЩНФМЕШРФОТДЦ") == 0,
              "Wheatstone two square cipher encryption is broken");
    char* decrypted = wheatstone_two_square_decrypt(encrypted);
    qc_assert(strcmp(decrypted, input) == 0,
              "Wheatstone two square cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

static void iteration(char const* input) {
    char* encrypted = wheatstone_two_square_encrypt(input);
    char* decrypted = wheatstone_two_square_decrypt(encrypted);
    qc_assert(strcmp(decrypted, input) == 0, "Wheatstone two square cipher is unreliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 0; i < SAMPLES_LENGTH; ++i) {
        iteration(samples[i]);
    }
}
