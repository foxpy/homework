#include <stdint.h>
#include "bit-array.h"
#include "serial.h"
#include "serial_impl.h"

static int process_packet(bits_t *dst, bits_t *packet, serial_cfg_t *cfg) {
	uint8_t sum = 0;
	bit b;
	if (next_bit(packet) != START_BIT)
		return -1;
	for (int i = 0; i < (int) cfg->data_bits; ++i) {
		b = next_bit(packet);
		bitarray_push_back(dst, b);
		sum += b;
	}
	if (cfg->parity_bit != PARITY_NONE)
		if (next_bit(packet) != parity(sum, cfg->parity_bit)) goto error;
	for (int i = 0; i < (int) cfg->stop_bits; ++i)
		if (next_bit(packet) != STOP_BIT) goto error;
	goto success;
error:
	for (int i = 0; i < (int) cfg->data_bits; ++i)
		bitarray_pop_back(dst);
	return -1;
success:
	return 0;
}

size_t serial_decode(bits_t *dst, bits_t *src, serial_cfg_t *cfg) {
	size_t ret = 0;
	bits_t window, tmp;
	bitarray_alloc(&window);
	for (unsigned char i = 0; i < serial_packet_length(cfg); ++i)
		bitarray_push_back(&window, next_bit(src));
	for (;;) {
		bitarray_copy(&tmp, &window);
		if (process_packet(dst, &tmp, cfg) != -1) {
			bitarray_free(&tmp);
			ret += 1;
			if (bitarray_empty(src)) break;
			bitarray_clear(&window);
			for (unsigned char i = 0; i < serial_packet_length(cfg); ++i)
				bitarray_push_back(&window, next_bit(src));
		} else {
			bitarray_free(&tmp);
			if (bitarray_empty(src)) break;
			bitarray_pop_front(&window);
			bitarray_push_back(&window, next_bit(src));
		}
	}
	bitarray_free(&window);
	return ret;
}
