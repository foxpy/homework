#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <qc.h>
#include "ciphers.h"

static void xorshift_impl(uint8_t const key[static 32], size_t len, uint8_t const input[static len],
                          uint8_t output[static len]) {
    uint64_t seed;
    memmove(&seed, key, 8);
    qc_rnd rnd;
    qc_rnd_seed(&rnd, seed);
    for (size_t i = 0; i < len; i += 8) {
        uint8_t estream[8];
        qc_rnd_buf(&rnd, 8, estream);
        uint8_t plaintext[8];
        size_t block_size = (len - i) >= 8 ? 8 : (len - i);
        memmove(plaintext, &input[i], block_size);
        uint8_t ciphertext[8];
        for (size_t j = 0; j < block_size; ++j) {
            ciphertext[j] = estream[j] ^ plaintext[j];
        }
        memmove(&output[i], ciphertext, block_size);
    }
}

void xorshift_encrypt(uint8_t const key[static 32], size_t len, uint8_t const input[static len],
                      uint8_t output[static len]) {
    xorshift_impl(key, len, input, output);
}

void xorshift_decrypt(uint8_t const key[static 32], size_t len, uint8_t const input[static len],
                      uint8_t output[static len]) {
    xorshift_impl(key, len, input, output);
}
