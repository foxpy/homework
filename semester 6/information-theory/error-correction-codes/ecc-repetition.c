#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cmdopts.h"
#include "bit-array.h"
#include "repetition-code.h"
#include "reopen-binary.h"

void encode_loop(FILE *input, FILE *output);
void decode_loop(FILE *input, FILE *output);

void help(char *program_name) {
	fprintf(stderr, "Usage: %s [OPTIONS] [INPUT] [OUTPUT]\n", program_name);
	fputs("INPUT - input file (stdin if \"-\" or omitted)\n", stderr);
	fputs("OUTPUT - output file (stdout if \"-\" or omitted)\n", stderr);
	fputs("OPTIONS - any of these:\n", stderr);
	fputs("\t--mode <encode | decode> - defaults to encode\n", stderr);
}

int main(int argc, char *argv[]) {
	REOPEN_BINARY_READ(stdin);
	REOPEN_BINARY_WRITE(stdout);
	int status = EXIT_SUCCESS;
	opts_t opts;
	enum {
		MODE_ENCODE,
		MODE_DECODE,
	} mode;
	cmdopts_parse(&opts, argc, argv);
	if (cmdopts_exists(&opts, "--help")) {
		help(argv[0]);
		return EXIT_SUCCESS;
	}

	if (cmdopts_exists(&opts, "--mode")) {
		char *val;
		if ((val = cmdopts_get_opt(&opts, "--mode")) == NULL) {
			help(argv[0]);
			return EXIT_FAILURE;
		}
		if (strcmp(val, "encode") == 0) {
			mode = MODE_ENCODE;
		} else if (strcmp(val, "decode") == 0) {
			mode = MODE_DECODE;
		} else {
			help(argv[0]);
			return EXIT_FAILURE;
		}
	} else {
		mode = MODE_ENCODE;
	}

	FILE *input = stdin;
	FILE *output = stdout;
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
		help(argv[0]);
		return EXIT_FAILURE;
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
	int c;
	unsigned char u;
	char *enc;
	size_t nbytes, nbits;
	bits_t binput, boutput;
	bitarray_alloc(&binput);
	bitarray_alloc(&boutput);
	while((c = fgetc(input)) != EOF) {
		u = (unsigned char) c;
		bitarray_fill_from_memory(&binput, &u, sizeof(unsigned char) * 8);
		repetition_encode(&boutput, &binput);
		enc = (char*) bitarray_to_memory(&boutput, &nbits, &nbytes);
		if (fwrite(enc, sizeof(char), nbytes, output) != nbytes) {
			free(enc);
			break;
		}
		free(enc);
	}
	bitarray_free(&boutput);
	bitarray_free(&binput);
}

void decode_loop(FILE *input, FILE *output) {
	char buf[3];
	char *dec;
	size_t nbytes, nbits;
	bits_t binput, boutput;
	bitarray_alloc(&binput);
	bitarray_alloc(&boutput);
	while (fread(buf, sizeof(char), 3, input) == 3) {
		bitarray_fill_from_memory(&binput, buf, sizeof(buf) * 8);
		repetition_decode(&boutput, &binput);
		dec = (char*) bitarray_to_memory(&boutput, &nbits, &nbytes);
		if (fputc(*dec, output) == EOF) {
			free(dec);
			break;
		}
		free(dec);
	}
	bitarray_free(&boutput);
	bitarray_free(&binput);
}
