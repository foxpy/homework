#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "util.h"
#include "reader.h"
#include "crc.h"

void continious_reader(struct thread_data *args) {
	uint8_t *data = args->ptr;
	struct timespec rqtp = { 0, args->interval };
	for (unsigned count = 0; count != args->count; ++count) {
#ifdef SYN_MUTEX
		pthread_mutex_lock(&args->mutex);
#endif
		printf("[%u] Reader: 0x%08x\n", count, crc32(data, args->len));
#ifdef SYN_MUTEX
		pthread_mutex_unlock(&args->mutex);
#endif
		nanosleep(&rqtp, NULL);
	}
	pthread_exit(NULL);
}
