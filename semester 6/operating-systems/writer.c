#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

#include "util.h"
#include "writer.h"
#include "crc.h"

static uint8_t xorshift32() {
	static uint32_t s = 0x92D68CA2;
	s ^= (s<<13);
	s ^= (s>>17);
	s ^= (s<<5);
	return (uint8_t) s;
}

void continious_writer(struct thread_data *args) {
	uint8_t *data = args->ptr;
	struct timespec rqtp = { 0, args->interval };
	for (unsigned count = 0; count != args->count; ++count) {
#ifdef SYN_MUTEX
		pthread_mutex_lock(&args->mutex);
#endif
		for (size_t i = 0; i < args->len; ++i)
			data[i] = xorshift32();
		printf("[%u] Writer: 0x%08x\n", count, crc32(data, args->len));
#ifdef SYN_MUTEX
		pthread_mutex_unlock(&args->mutex);
#endif
		nanosleep(&rqtp, NULL);
	}
	pthread_exit(NULL);
}
