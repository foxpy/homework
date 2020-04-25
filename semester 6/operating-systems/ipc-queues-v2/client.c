#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/msg.h>
#include "help.h"
#include "msg.h"

int main(int argc, char *argv[]) {
	key_t key;
	int qid;
	msg_t msg;
	struct timespec rqtp;
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
	if ((qid = msgget(key, 0)) == -1) {
		perror("msgget");
		return EXIT_FAILURE;
	}
	msg.mtype = getpid();
	rqtp.tv_sec = 0;
	for (int i = 0; i < 8; ++i) {
		rqtp.tv_nsec = i * (int)(1e8);
		snprintf(msg.mtext, sizeof(msg.mtext), "%d+%d=%d", i, 2*i, i+2*i);
		if (msgsnd(qid, &msg, sizeof(msg), !IPC_NOWAIT) == -1)
			fprintf(stderr, "Warning: failed to send message \"%-64s\"\n", msg.mtext);
		nanosleep(&rqtp, NULL);
	}
	return EXIT_SUCCESS;
}
