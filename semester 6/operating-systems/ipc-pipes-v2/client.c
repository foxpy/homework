#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void help(char *program_name);

int main(int argc, char *argv[]) {
	int interval, counter, fifo_fd;
	pid_t pid;
	char buf[256];
	if (argc != 3) {
		help(argv[0]);
		return EXIT_FAILURE;
	}
	interval = atoi(argv[2]);
	if (interval <= 0 || interval > 100) {
		fprintf(stderr, "Error: \"%s\" in not a valid interval\n", argv[2]);
		help(argv[0]);
		return EXIT_FAILURE;
	}
	if ((fifo_fd = open(argv[1], O_WRONLY)) == -1) {
		fprintf(stderr, "Failed to open FIFO \"%s\" for writing: %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	pid = getpid();

	counter = 0;
	snprintf(buf, sizeof(buf), "Hello from %d\n", pid);
	while (write(fifo_fd, buf, strlen(buf)) != -1) {
		snprintf(buf, sizeof(buf), "[%d] says %d\n", pid, ++counter);
		sleep(interval);
	}

	close(fifo_fd);
	return EXIT_SUCCESS;
}

void help(char *program_name) {
	fprintf(stderr, "Usage: %s FIFO TIME\n", program_name);
	fputs("\tFIFO: file name used for communication\n", stderr);
	fputs("\tTIME: interval in seconds (> 0 && <= 100) between data transfers\n", stderr);
}
