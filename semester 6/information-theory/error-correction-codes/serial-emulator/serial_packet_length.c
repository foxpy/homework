#include "serial.h"

unsigned char serial_packet_length(serial_cfg_t *cfg) {
	unsigned char len = 1; // start bit
	len += cfg->data_bits;
	len += (cfg->parity_bit == PARITY_NONE) ? 0 : 1;
	len += cfg->stop_bits;
	return len;
}
