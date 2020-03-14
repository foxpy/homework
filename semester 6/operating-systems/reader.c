#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "util.h"
#include "reader.h"

void continious_reader(struct thread_data *args) {
	uint8_t *data = args->ptr;
	struct timespec rqtp = { 0, args->interval };
	for (unsigned count = 0; count != args->count; ++count) {
		fputs("0x", stdout);
		for (size_t i = 0; i != args->len; ++i)
			printf("%02hhx", data[i]);
		fputc('\n', stdout);
		nanosleep(&rqtp, NULL);
	}
	pthread_exit(NULL);
}
