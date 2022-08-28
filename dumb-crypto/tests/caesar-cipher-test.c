#include <string.h>
#include "qc.h"
#include "crypto.h"

void simple_test() {
    char* encrypted = caesar_cipher_encrypt("ПРИВЕТ", 1);
    qc_assert(strcmp(encrypted, "РСЙГЁУ") == 0, "Caesar encryption is broken");
    char* decrypted = caesar_cipher_decrypt(encrypted, 1);
    qc_assert(strcmp(decrypted, "ПРИВЕТ") == 0, "Caesar decryption is broken");
    free(encrypted);
    free(decrypted);
}

void iteration(size_t key) {
    char* msg = "ДЛИННОЕТЕСТОВОЕСООБЩЕНИЕ";
    char* encrypted = caesar_cipher_encrypt(msg, key);
    char* decrypted = caesar_cipher_decrypt(encrypted, key);
    qc_assert(strcmp(msg, decrypted) == 0, "Caesar cipher is not reliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 1; i < 32; ++i) {
        iteration(i);
    }
}
