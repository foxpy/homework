#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "cmdopts.h"
#include "reopen-binary.h"
#include "hamming-code.h"

void encode_loop(FILE *input, FILE *output);
void decode_loop(FILE *input, FILE *output);

void help(char *program_name, int status) {
	fprintf(stderr, "Usage: %s [--mode <encode | decode>] [INPUT] [OUTPUT]\n", program_name);
	fputs("\tINPUT - input file (stdin if \"-\" or omitted)\n", stderr);
	fputs("\tOUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fputs("\tDefault mode is encode\n", stderr);
	exit(status);
}

int main(int argc, char *argv[]) {
	REOPEN_BINARY_READ(stdin);
	REOPEN_BINARY_WRITE(stdout);
	int status = EXIT_SUCCESS;
	opts_t opts;
	FILE *input = stdin;
	FILE *output = stdout;
	enum {
		MODE_ENCODE,
		MODE_DECODE,
	} mode;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help"))
		help(argv[0], EXIT_SUCCESS);
	if (cmdopts_exists(&opts, "--mode")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--mode")) == NULL) {
			help(argv[0], EXIT_FAILURE);
		}
		if (strcmp(val, "encode") == 0) {
			mode = MODE_ENCODE;
		} else if (strcmp(val, "decode") == 0) {
			mode = MODE_DECODE;
		} else {
			help(argv[0], EXIT_FAILURE);
		}
	} else {
		mode = MODE_ENCODE;
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
	if (cmdopts_num_posopts(&opts) > 2) {
		help(argv[0], EXIT_FAILURE);
	}

	switch (mode) {
	case MODE_ENCODE:
		encode_loop(input, output);
		break;
	case MODE_DECODE:
		decode_loop(input, output);
		break;
	}

	if (output != stdout) fclose(output);
error_open_output:
	if (input != stdin) fclose(input);
error_open_input:
	cmdopts_free(&opts);
	return status;
}

void encode_loop(FILE *input, FILE *output) {
	unsigned char buf, *mem;
	bits_t bit_input, bit_output;
	size_t nbits, nbytes;
	bitarray_alloc(&bit_input);
	bitarray_alloc(&bit_output);
	while (fread(&buf, sizeof(unsigned char), 1, input) == 1) {
		bitarray_fill_from_memory(&bit_input, &buf, 8);
		hamming_encode(&bit_output, &bit_input);
		mem = bitarray_to_memory(&bit_output, &nbits, &nbytes);
		if (fwrite(mem, sizeof(unsigned char), nbytes, output) != nbytes) break;
		free(mem);
	}
	bitarray_free(&bit_input);
	bitarray_free(&bit_output);
}

void decode_loop(FILE *input, FILE *output) {
	fputs("Not implemented yet...\n", stderr);
	exit(EXIT_SUCCESS);
}