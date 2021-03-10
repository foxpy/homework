#include <sys/random.h>
#include <string.h>
#include "gost.h"

void gost_key(gost* g, uint32_t key[8]) {
	getrandom(g->key, 8 * sizeof(uint32_t), 0);
	if (key) memmove(key, g->key, 8 * sizeof(uint32_t));
	else die("Failed to obtain key");
}
