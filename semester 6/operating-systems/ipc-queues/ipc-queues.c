#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdbool.h>

void help(const char *program_name);

int main(int argc, char *argv[]) {
	bool sender_mode;
	mqd_t queue;
	char buf[BUFSIZ];
	size_t read_size;
	ssize_t mq_size;

	if (argc != 3) {
		help(argv[0]);
		return EXIT_FAILURE;
	}
	if (strcmp(argv[1], "sender") == 0) {
		sender_mode = true;
	} else if (strcmp(argv[1], "receiver") == 0) {
		sender_mode = false;
	} else {
		fprintf(stderr, "Invalid operation mode: \"%s\"\n", argv[1]);
		return EXIT_FAILURE;
	}

	if (sender_mode) {
		if ((queue = mq_open(argv[2], O_WRONLY)) == (mqd_t) -1) {
			perror("mq_open");
			return EXIT_FAILURE;
		}
	} else {
		if ((queue = mq_open(argv[2], O_RDONLY | O_CREAT, 0777, NULL)) == (mqd_t) -1) {
			perror("mq_open");
			return EXIT_FAILURE;
		}
	}

	if (sender_mode) {
		if ((read_size = fread(buf, sizeof(char), BUFSIZ, stdin)) == 0) {
			fputs("Could not read from stdin\n", stderr);
			return EXIT_FAILURE;
		}
		if (mq_send(queue, buf, BUFSIZ, 1) == -1) {
			perror("mq_send");
			return EXIT_FAILURE;
		}
	} else {
		if ((mq_size = mq_receive(queue, buf, BUFSIZ, NULL)) == -1) {
			perror("mq_receive");
			return EXIT_FAILURE;
		}
		buf[mq_size] = '\0';
		printf("Received data: %s\n", buf);
	}

	mq_close(queue);
	if (!sender_mode)
		mq_unlink(argv[2]);
	return EXIT_SUCCESS;
}

void help(const char *program_name) {
	fprintf(stderr, "Usage: %s <sender|receiver> NAME\n", program_name);
	fputs("\tNAME - message queue name, e.g. \"/example\"\n", stderr);
	fputs("\tIn sender mode, data is read from stdin\n", stderr);
	fputs("\tIn receiver mode, data is written to stdout\n", stderr);
}
