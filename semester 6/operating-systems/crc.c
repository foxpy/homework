#include <stdlib.h>
#include <stdint.h>

#include "crc.h"

uint32_t crc32(void *src, size_t len) {
	uint8_t *input = src;
	uint32_t val, crc = 0xFFFFFFFF;

	for (size_t i = 0; i < len; ++i) {
		val = (crc ^ input[i]) & 0xFF;
		for (size_t j = 0; j < 8; ++j)
			val = (val & 0x01) ? ((val>>1) ^ 0xEDB88320) : (val>>1);
		crc = val ^ (crc>>8);
	}
	crc ^= 0xFFFFFFFF;
	return crc;
}
