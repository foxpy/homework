#include <stdint.h>
#include "random.h"
#include "random_impl.h"

void xorshift64(uint64_t *s) {
	*s ^= *s << 21;
	*s ^= *s >> 15;
	*s ^= *s << 29;
}
