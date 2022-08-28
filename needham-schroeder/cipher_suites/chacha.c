#include <chacha20.h>
#include "ciphers.h"

void chacha20_encrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t const nonce[static 12],
                               uint8_t buf[static len]) {
    chacha20_state* cc20 = chacha20_new(key, nonce);
    chacha20_encrypt_bytes(cc20, len, buf);
    chacha20_free(cc20);
}

void chacha20_decrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t const nonce[static 12],
                               uint8_t buf[static len]) {
    chacha20_state* cc20 = chacha20_new(key, nonce);
    chacha20_decrypt_bytes(cc20, len, buf);
    chacha20_free(cc20);
}
