#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "cmdopts.h"
#include "serial.h"
#include "bit-array.h"
#include "emalloc.h"
#include "lcm.h"
#include "reopen-binary.h"

void help(char *program_name, int exit_status) {
	fprintf(stderr, "Usage: %s [OPTIONS] [INPUT] [OUTPUT]\n", program_name);
	fputs("INPUT - input file (stdin if \"-\" or omitted)\n", stderr);
	fputs("OUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fputs("OPTIONS - any of these:\n", stderr);
	fputs("\t--mode <encode | decode> - defaults to encode\n", stderr);
	fputs("\t--data-bits <5 | 6 | 7 | 8 | 9> - defaults to 8\n", stderr);
	fputs("\t--parity <none | odd | even> - defaults to none\n", stderr);
	fputs("\t--stop-bits <1 | 2> - defaults to 1\n", stderr);
	fputs("In encode mode, program prints number of encoded packets to stderr.\n", stderr);
	fputs("In decode mode, program prints number of detected errors to stderr.\n", stderr);
	exit(exit_status);
}

void encode_loop(FILE *input, FILE *output, serial_cfg_t *cfg);
void decode_loop(FILE *input, FILE *output, serial_cfg_t *cfg);

int main(int argc, char *argv[]) {
	REOPEN_BINARY_READ(stdin);
	REOPEN_BINARY_WRITE(stdout);
	opts_t opts;
	serial_cfg_t cfg = { 8, PARITY_NONE, 1 };
	enum {
		ENCODE,
		DECODE,
	} mode = ENCODE;
	FILE *input = stdin;
	FILE *output = stdout;
	int status = EXIT_SUCCESS;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help"))
		help(argv[0], EXIT_SUCCESS);
	if (cmdopts_exists(&opts, "--mode")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--mode")) == NULL)
			help(argv[0], EXIT_FAILURE);
		for (unsigned long i = 0; i < strlen(val); ++i) val[i] = tolower(val[i]);
		if (strcmp(val, "encode") == 0)
			mode = ENCODE;
		else if (strcmp(val, "decode") == 0)
			mode = DECODE;
		else
			help(argv[0], EXIT_FAILURE);
	}
	if (cmdopts_exists(&opts, "--data-bits")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--data-bits")) == NULL)
			help(argv[0], EXIT_FAILURE);
		int data_bits = atoi(val);
		if (data_bits < 5 || data_bits > 9) help(argv[0], EXIT_FAILURE);
		cfg.data_bits = data_bits;
	}
	if (cmdopts_exists(&opts, "--parity")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--parity")) == NULL)
			help(argv[0], EXIT_FAILURE);
		for (unsigned long i = 0; i < strlen(val); ++i) val[i] = tolower(val[i]);
		if (strcmp(val, "none") == 0)
			cfg.parity_bit = PARITY_NONE;
		else if (strcmp(val, "odd") == 0)
			cfg.parity_bit = PARITY_ODD;
		else if (strcmp(val, "even") == 0)
			cfg.parity_bit = PARITY_EVEN;
		else
			help(argv[0], EXIT_FAILURE);
	}
	if (cmdopts_exists(&opts, "--stop-bits")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--stop-bits")) == NULL)
			help(argv[0], EXIT_FAILURE);
		int stop_bits = atoi(val);
		if (stop_bits < 1 || stop_bits > 2) help(argv[0], EXIT_FAILURE);
		cfg.stop_bits = stop_bits;
	}
	if (cmdopts_num_posopts(&opts) > 0) {
		if (strcmp(cmdopts_get_posopt(&opts, 0), "-") != 0) {
			if ((input = fopen(cmdopts_get_posopt(&opts, 0), "rb")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 0), strerror(errno));
				status = EXIT_FAILURE;
				goto error_open_input;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 1) {
		if (strcmp(cmdopts_get_posopt(&opts, 1), "-") != 0) {
			if ((output = fopen(cmdopts_get_posopt(&opts, 1), "wb")) == NULL) {
				fprintf(stderr, "Failed to open file %s: %s\n", cmdopts_get_posopt(&opts, 1), strerror(errno));
				status = EXIT_FAILURE;
				goto error_open_output;
			}
		}
	}
	if (cmdopts_num_posopts(&opts) > 2)
		help(argv[0], EXIT_FAILURE);

	if (mode == ENCODE)
		encode_loop(input, output, &cfg);
	else
		decode_loop(input, output, &cfg);

	if (output != stdout) fclose(output);
error_open_output:
	if (input != stdin) fclose(input);
error_open_input:
	cmdopts_free(&opts);
	return status;
}

void encode_loop(FILE *input, FILE *output, serial_cfg_t *cfg) {
	size_t buf_size = lcm(lcm(serial_packet_length(cfg), cfg->data_bits), 8) / 8;
	size_t nread, nbits, nbytes, npackets = 0;
	uint8_t *encoded, *buf = (uint8_t*) emalloc(buf_size);
	bits_t bit_input, bit_output;
	bitarray_alloc(&bit_input);
	bitarray_alloc(&bit_output);
	while ((nread = fread(buf, sizeof(uint8_t), buf_size, input)) > 0) {
		bitarray_fill_from_memory(&bit_input, buf, nread * sizeof(uint8_t) * 8);
		npackets += serial_encode(&bit_output, &bit_input, cfg);
		encoded = bitarray_to_memory(&bit_output, &nbits, &nbytes);
		fwrite(encoded, sizeof(uint8_t), nbytes, output);
		free(encoded);
	}
	bitarray_free(&bit_input);
	bitarray_free(&bit_output);
	free(buf);
	fprintf(stderr, "%zu\n", npackets);
}

void decode_loop(FILE *input, FILE *output, serial_cfg_t *cfg) {
	fputs("Unimplemented\n", stderr);
	fputs("Current Serial API is not designed well to support stream decoding\n", stderr);
}
