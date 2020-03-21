#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "util.h"
#include "reader.h"
#include "crc.h"

#include "config.h"
#ifdef SYN_SEMA
#include <semaphore.h>
#endif
#ifdef SYN_ATOM
#include <stdatomic.h>
#endif

void continious_reader(struct thread_data *args) {
	uint8_t *data = args->ptr;
	struct timespec rqtp = { 0, args->interval };
	for (unsigned count = 0; count != args->count; ++count) {
#		ifdef SYN_MUTEX
			pthread_mutex_lock(&args->mutex);
#		endif
#		ifdef SYN_SEMA
			sem_wait(&args->semaphore);
#		endif
#		ifdef SYN_ATOM
			while (atomic_flag_test_and_set_explicit(
			       &args->lock, memory_order_acquire)) {}
#		endif
		printf("[%u] Reader: 0x%08x\n", count, crc32(data, args->len));
#		ifdef SYN_MUTEX
			pthread_mutex_unlock(&args->mutex);
#		endif
#		ifdef SYN_SEMA
			sem_post(&args->semaphore);
#		endif
#		ifdef SYN_ATOM
			atomic_flag_clear_explicit(&args->lock, memory_order_release);
#		endif
		nanosleep(&rqtp, NULL);
	}
	pthread_exit(NULL);
}
