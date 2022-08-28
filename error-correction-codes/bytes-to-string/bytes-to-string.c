#include <stdlib.h>
#include <stdio.h>
#include "bytes-to-string.h"

void bytes_to_bitstring(void *dst, void *src, size_t len) {
	unsigned char *d = dst, *s = src;
	for (size_t i = 0; i < len; ++i) {
		d[8*i+0] = (s[i] & 0x01u) ? '1' : '0';
		d[8*i+1] = (s[i] & 0x02u) ? '1' : '0';
		d[8*i+2] = (s[i] & 0x04u) ? '1' : '0';
		d[8*i+3] = (s[i] & 0x08u) ? '1' : '0';
		d[8*i+4] = (s[i] & 0x10u) ? '1' : '0';
		d[8*i+5] = (s[i] & 0x20u) ? '1' : '0';
		d[8*i+6] = (s[i] & 0x40u) ? '1' : '0';
		d[8*i+7] = (s[i] & 0x80u) ? '1' : '0';
	}
	d[8*len+0] = '\0';
}

void bytes_to_hexstring(void *dst, void *src, size_t len) {
	char *d = dst, *s = src;
	char buf[3];
	for (size_t i = 0; i < len; ++i) {
		sprintf(buf, "%02hhx", s[i]);
		d[2*i+0] = buf[0];
		d[2*i+1] = buf[1];
	}
	d[2*len+0] = '\0';
}
