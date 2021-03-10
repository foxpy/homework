#include "gost.h"

static void gostcrypt(gost* g, uint32_t* d) {
	uint32_t n1 = d[0], n2 = d[1];
	uint32_t* k = g->key;
	for (size_t i = 0; i < 3; ++i) {
		n2 ^= f(g, n1 + k[0]); n1 ^= f(g, n2 + k[1]);
		n2 ^= f(g, n1 + k[2]); n1 ^= f(g, n2 + k[3]);
		n2 ^= f(g, n1 + k[4]); n1 ^= f(g, n2 + k[5]);
		n2 ^= f(g, n1 + k[6]); n1 ^= f(g, n2 + k[7]);
	}
	n2 ^= f(g, n1 + k[7]); n1 ^= f(g, n2 + k[6]);
	n2 ^= f(g, n1 + k[5]); n1 ^= f(g, n2 + k[4]);
	n2 ^= f(g, n1 + k[3]); n1 ^= f(g, n2 + k[2]);
	n2 ^= f(g, n1 + k[1]); n1 ^= f(g, n2 + k[0]);
	d[0] = n2; d[1] = n1;
}

void gost_encrypt(gost* g, uint32_t* buf, size_t len) {
	for (size_t i = 0; i < len; ++i) {
		gostcrypt(g, &buf[2*i]);
	}
}
