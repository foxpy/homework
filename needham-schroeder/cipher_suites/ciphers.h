#pragma once
#include <stdint.h>
#include <stddef.h>

#define XORSHIFT_CIPHER 0
#define CHACHA20_CIPHER 1

void xorshift_encrypt(uint8_t const key[static 32], size_t len, uint8_t const input[static len],
                      uint8_t output[static len]);
void xorshift_decrypt(uint8_t const key[static 32], size_t len, uint8_t const input[static len],
                      uint8_t output[static len]);
void chacha20_encrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t const nonce[static 12],
                      uint8_t buf[static len]);
void chacha20_decrypt_in_place(uint8_t const key[static 32], size_t len, uint8_t const nonce[static 12],
                      uint8_t buf[static len]);
