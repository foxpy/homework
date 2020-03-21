#pragma once
#include <stdlib.h>
#include <pthread.h>

#include "config.h"
#ifdef SYN_SEMA
#include <semaphore.h>
#endif

struct thread_data {
	void *ptr;         // size of memory buffer
	size_t len;        // length of memory buffer
	unsigned interval; // sleep for `interval` nsecs between memory actions
	unsigned count;    // perform memory action `count` times

	// only one thread at time should access memory
#	ifdef SYN_MUTEX
		pthread_mutex_t mutex;
#	endif
#	ifdef SYN_SEMA
		sem_t semaphore;
#	endif
};
