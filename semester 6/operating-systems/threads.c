#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

#include "util.h"
#include "writer.h"
#include "reader.h"

#include "config.h"
#ifdef SYN_SEMA
#include <semaphore.h>
#endif

#define DEFAULT_BUFFER_SIZE 0x100000
#define DEFAULT_SLEEP_INTERVAL_NSECS 10000
#define DEFAULT_ITERATIONS 8

#define die(msg) { fputs(msg, stderr); return EXIT_FAILURE; }
static void usage(const char *program_name);

int main(int argc, char *argv[]) {
	if (argc != 4 && argc != 1) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	size_t buffer_size;
	unsigned sleep_interval;
	unsigned iterations;
	if (argc == 4) {
		if ((buffer_size = (size_t) (atoll(argv[1]))) == 0)
			die("Fatal error: expected positive integer SIZE\n");
		if ((sleep_interval = (unsigned) (atol(argv[2]))) == 0)
			die("Fatal error: expected positive integer INTERVAL\n");
		if ((iterations = (unsigned) (atol(argv[3]))) == 0)
			die("Fatal error: expected positive integer ITERATIONS\n");
	} else {
		buffer_size = DEFAULT_BUFFER_SIZE;
		sleep_interval = DEFAULT_SLEEP_INTERVAL_NSECS;
		iterations = DEFAULT_ITERATIONS;
	}

	uint8_t *data = (uint8_t*) calloc(buffer_size, sizeof(uint8_t));
	struct thread_data args = {
		data,
		buffer_size,
		sleep_interval,
		iterations,
#		ifdef SYN_MUTEX
			PTHREAD_MUTEX_INITIALIZER,
#		endif
#		ifdef SYN_SEMA
			0,
#		endif
	};
	pthread_t threads[2];

#	ifdef SYN_SEMA
		sem_init(&args.semaphore, 0, 1);
#	endif
	pthread_create(&threads[0], NULL, (void*) continious_writer, &args);
	pthread_create(&threads[1], NULL, (void*) continious_reader, &args);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	free(data);
	return EXIT_SUCCESS;
}

void usage(const char* program_name) {
	fprintf(stderr, "Usage: %s [SIZE INTERVAL ITERATIONS]\n", program_name);
	fputs("\tSIZE - size of memory buffer\n", stderr);
	fputs("\tINTERVAL - sleep interval between memory operations\n", stderr);
	fputs("\tITERATIONS - number of iterations per thread\n", stderr);
}
