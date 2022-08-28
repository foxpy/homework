#include <stddef.h>
#include <string.h>
#include "qc.h"
#include "crypto.h"

static char const* keys[] = {
        "РАБОТА",
        "САМОЛЕТ",
        "АВТОМОБИЛЬ",
        "ДОМАШНЯЯРАБОТА",
        "ЗАЧЕМЯЭТОДЕЛАЮМНЕПЛОХОПОМОГИТЕПОЖАЛУЙСТА"
};
#define KEYS_LENGTH (sizeof(keys)/sizeof(keys[0]))

void simple_test() {
    char const* input = "ПРИЛЕТАЮЗАВТРА";
    char* encrypted = playfair_cipher_encrypt(input, 8, 4, keys[0]);
    qc_assert(strcmp(encrypted, "НАЙМЙРГЩЖБГВАБ") == 0, "Playfair cipher encryption is broken");
    char* decrypted = playfair_cipher_decrypt(encrypted, 8, 4, keys[0]);
    qc_assert(strcmp(decrypted, "ПРИЛЕТАЮЗАВТРА") == 0, "Playfair cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

void scary_test() {
    char* encrypted = playfair_cipher_encrypt("ЭЭТТООТТШШИИФФРРУУЖЖААССЕЕНН", 8, 4, keys[0]);
    char* decrypted = playfair_cipher_decrypt(encrypted, 8, 4, keys[0]);
    qc_assert(strcmp(decrypted, "ЭЪЭТТООТТШШИИФФРРУУЖЖААССЕЕННЪ") == 0,
              "Playfair cipher is kinda broken");
    free(encrypted);
    free(decrypted);
}

// we call it a simple iteration because Playfair cipher is so inferior
// you can't guarantee that input == Decrypt(Encrypt(input, key), key)
// so we have to carefully pick inputs which are guaranteed to succeed
// in this test :(
// ***
// also Playfair cipher highly depends on alphabet so we can only use
// matrix 8x4 in this particular implementation xD
// I could add an API which accepts a custom alphabet but that's too
// much of a hassle for such stupid homework, egh :(
void simple_iteration(char const* key) {
    char const* input = "ЗДРАВСТВУЙТЕ";
    char* encrypted = playfair_cipher_encrypt(input, 8, 4, key);
    char* decrypted = playfair_cipher_decrypt(encrypted, 8, 4, key);

    // it is broken by design though
    qc_assert(strcmp(input, decrypted) == 0, "Playfair cipher is broken");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    scary_test();
    for (size_t i = 0; i < KEYS_LENGTH; ++i) {
        simple_iteration(keys[i]);
    }
}
