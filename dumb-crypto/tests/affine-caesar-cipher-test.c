#include <string.h>
#include "qc.h"
#include "crypto.h"

void simple_test() {
    char* encrypted = affine_caesar_cipher_encrypt("ПРИВЕТ", 7, 1);
    qc_assert(strcmp(encrypted, "НФЮОГВ") == 0, "Affine Caesar encryption is broken");
    char* decrypted = affine_caesar_cipher_decrypt(encrypted, 7, 1);
    qc_assert(strcmp(decrypted, "ПРИВЕТ") == 0, "Affine Caesar decryption is broken");
    free(encrypted);
    free(decrypted);
}

void iteration(size_t a, size_t b) {
    char* msg = "ДЛИННОЕТЕСТОВОЕСООБЩЕНИЕ";
    char* encrypted = affine_caesar_cipher_encrypt(msg, a, b);
    char* decrypted = affine_caesar_cipher_decrypt(encrypted, a, b);
    qc_assert(strcmp(msg, decrypted) == 0, "Affine Caesar cipher is not reliable");
    free(encrypted);
    free(decrypted);
}

int main() {
    simple_test();
    for (size_t i = 1; i < 32; ++i) {
        for (size_t j = 1; j < 32; ++j) {
            if (gcd(i, 33) == 1) {
                iteration(i, j);
            }
        }
    }
}
