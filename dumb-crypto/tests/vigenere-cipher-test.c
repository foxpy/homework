#include <string.h>
#include "crypto.h"
#include "qc.h"

static char const* samples[] = {
        "РАБОТА",
        "ПРИЛЕТАЮДЕСЯТОГО",
        "ЯРЙЩЧТРЮЕУГЯВОДЬ",
        "АВТОБУС",
        "ВЕРТОЛЕТ",
        "ТАНК",
        "ДОВОЛЬНОДЛИННАЯСТРОКА",
        "ЭТОТШИФРПОЛУЧШЕПЛЕЙФЕРАБУДЕТ",
        "НОВСЕРАВНОНЕОЧ",
        "УГУ"
};
#define SAMPLES_LENGTH (sizeof(samples)/sizeof(samples[0]))

void simple_test() {
    char* encrypted = vigenere_cipher_encrypt(samples[1], samples[0]);
    qc_assert(strcmp(encrypted, samples[2]) == 0, "Vigenere cipher encryption is broken");
    char* decrypted = vigenere_cipher_decrypt(encrypted, samples[0]);
    qc_assert(strcmp(decrypted, samples[1]) == 0, "Vigenere cipher decryption is broken");
    free(encrypted);
    free(decrypted);
}

void iteration(char const* input, char const* key) {
    char* encrypted = vigenere_cipher_encrypt(input, key);
    char* decrypted = vigenere_cipher_decrypt(encrypted, key);
    qc_assert(strcmp(decrypted, input) == 0, "Vigenere cipher is unreliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 0; i < SAMPLES_LENGTH; ++i) {
        for (size_t j = 0; j < SAMPLES_LENGTH; ++j) {
            iteration(samples[i], samples[j]);
        }
    }
}
