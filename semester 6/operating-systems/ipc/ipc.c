#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sender.h"
#include "receiver.h"
void help(const char *program_name);

int main(int argc, char *argv[]) {
	enum {
		SENDER,
		RECEIVER,
	} operation_mode;
	FILE *file, *fifo;
	char *file_open_mode, *fifo_open_mode;

	if (argc != 4) {
		help(argv[0]);
		return EXIT_FAILURE;
	}
	if (strcmp(argv[1], "sender") == 0) {
		operation_mode = SENDER;
		file_open_mode = "r";
		fifo_open_mode = "w";
	} else if (strcmp(argv[1], "receiver") == 0) {
		operation_mode = RECEIVER;
		file_open_mode = "w";
		fifo_open_mode = "r";
	} else {
		fprintf(stderr, "Invalid operation MODE: \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}
	if ((file = fopen(argv[2], file_open_mode)) == NULL) {
		perror("fopen(FILE)");
		return EXIT_FAILURE;
	}
	if ((fifo = fopen(argv[3], fifo_open_mode)) == NULL) {
		perror("fopen(FIFO)");
		return EXIT_FAILURE;
	}

	switch(operation_mode) {
	case SENDER:
		sender(file, fifo);
		break;
	case RECEIVER:
		receiver(file, fifo);
		break;
	}

	return EXIT_SUCCESS;
}

void help(const char *program_name) {
	fprintf(stderr, "Usage: %s MODE FILE FIFO\n", program_name);
	fputs("\tMODE: <sender/receiver>\n", stderr);
	fputs("\tFILE: input file for sender mode, output file for receiver mode\n", stderr);
	fputs("\tFIFO: file to use for interprocess communication\n", stderr);
}
