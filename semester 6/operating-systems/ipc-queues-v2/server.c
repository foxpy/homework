#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include "help.h"
#include "msg.h"

int qid;

void sig_handler(int signo) {
	switch (signo) {
	case SIGINT:
		msgctl(qid, IPC_RMID, NULL);
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char *argv[]) {
	key_t key;
	msg_t msg;
	if (argc != 3) {
		help(argv[0]);
		return EXIT_FAILURE;
	}
	if (strlen(argv[2]) != 1 || !isalpha(argv[2][0])) {
		fprintf(stderr, "Error: \"%s\" is not an alphabetic character\n", argv[2]);
		help(argv[0]);
		return EXIT_FAILURE;
	}
	if ((key = ftok(argv[1], argv[2][0])) == -1) {
		fprintf(stderr, "Failed to obtain System V IPC key on file \"%s\": %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	if ((qid = msgget(key, IPC_CREAT | RW_RW_RW_)) == -1) {
		perror("msgget");
		return EXIT_FAILURE;
	}
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		fputs("Warning: failed to set signal handler, you will probably have to delete queue manually\n", stderr);
	for (;;) {
		if (msgrcv(qid, &msg, sizeof(msg), 0, !IPC_NOWAIT) == -1)
			fprintf(stderr, "Warning: failed to receiver message: %s\n", strerror(errno));
		printf("Received message from %ld: \"%-64s\"\n", msg.mtype, msg.mtext);
	}
	return EXIT_SUCCESS;
}
