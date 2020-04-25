#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <time.h>
#include <sys/stat.h>

#define RW_RW_RW_ 0666
void help(char *program_name);

int main(int argc, char *argv[]) {
	int duration, timeout, fifo_fd, stdout_fd;
	ssize_t nread;
	struct timespec tp, tp_shutdown;
	char buf[BUFSIZ];
	struct pollfd fds[1];

	if (argc != 3) {
		help(argv[0]);
		return EXIT_FAILURE;
	}
	duration = atoi(argv[2]);
	if (duration <= 0 || duration > 1000) {
		fprintf(stderr, "Error: \"%s\" in not a valid duration\n", argv[2]);
		help(argv[0]);
		return EXIT_FAILURE;
	}
	if (mknod(argv[1], S_IFIFO | RW_RW_RW_, 0) == -1) {
		fprintf(stderr, "Failed to create FIFO \"%s\": %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	if ((fifo_fd = open(argv[1], O_RDONLY | O_NONBLOCK)) == -1) {
		fprintf(stderr, "Failed to open FIFO \"%s\" for reading: %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	fds[0].fd = fifo_fd;
	fds[0].events = POLLIN;
	if (clock_gettime(CLOCK_BOOTTIME, &tp) == -1) {
		fprintf(stderr, "Failed to get CLOCK_BOOTIME: %s", strerror(errno));
		return EXIT_FAILURE;
	}
	memcpy(&tp_shutdown, &tp, sizeof(struct timespec));
	tp_shutdown.tv_sec += duration;

	stdout_fd = fileno(stdout);
	while (tp.tv_sec < tp_shutdown.tv_sec || (tp.tv_sec == tp_shutdown.tv_sec && tp.tv_nsec < tp_shutdown.tv_nsec)) {
		if (tp.tv_sec < tp_shutdown.tv_sec)
			timeout = (tp_shutdown.tv_sec - tp.tv_sec) * 1000;
		else
			timeout = (tp_shutdown.tv_nsec - tp.tv_nsec) / (int)(1e6);
		if (poll(fds, 1, timeout) > 0 && fds[0].revents & POLLIN) {
			while ((nread = read(fifo_fd, buf, BUFSIZ)) != -1) {
				if (write(stdout_fd, buf, nread) == -1) {
					fputs("Unexpected failure during writing data to stdout\n", stderr);
					break;
				}
			}
		}
		clock_gettime(CLOCK_BOOTTIME, &tp);
	}

	close(fifo_fd);
	if (remove(argv[1]) == -1) {
		fprintf(stderr, "Warning: failed to remove FIFO \"%s\": %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	} else {
		return EXIT_SUCCESS;
	}
}

void help(char *program_name) {
	fprintf(stderr, "Usage: %s FIFO TIME\n", program_name);
	fputs("\tFIFO: file name used for communication\n", stderr);
	fputs("\tTIME: duration in seconds (> 0 && <= 1000) during which server executes\n", stderr);
}
