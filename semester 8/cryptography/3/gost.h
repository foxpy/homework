#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

typedef struct {
	uint32_t key[8];
	char k87[256];
	char k65[256];
	char k43[256];
	char k21[256];
} gost;

void gost_encrypt(gost* g, uint32_t* buf, size_t len);
void gost_decrypt(gost* g, uint32_t* buf, size_t len);
void gost_key(gost* g, uint32_t buf[8]);
void gost_init(gost* g);

uint32_t rotl32(uint32_t x, size_t n);
uint32_t f(gost* g, uint32_t x);

void die(char const* msg);
void print_key(uint32_t const key[8]);
