#include "gost.h"

void gost_init(gost* g) {
	uint8_t k8[16] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7};
	uint8_t k7[16] = {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10};
	uint8_t k6[16] = {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8};
	uint8_t k5[16] = {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15};
	uint8_t k4[16] = {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9};
	uint8_t k3[16] = {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11};
	uint8_t k2[16] = {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1};
	uint8_t k1[16] = {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7};
	for (size_t i = 0; i < 256; ++i) {
		g->k87[i] = k8[i >> 4] << 4 | k7[i & 15];
		g->k65[i] = k6[i >> 4] << 4 | k5[i & 15];
		g->k43[i] = k4[i >> 4] << 4 | k3[i & 15];
		g->k21[i] = k2[i >> 4] << 4 | k1[i & 15];
	}
}
