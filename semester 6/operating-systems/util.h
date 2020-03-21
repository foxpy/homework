#pragma once
#include <stdlib.h>
#include <pthread.h>
#include "config.h"

struct thread_data {
	void *ptr;             // size of memory buffer
	size_t len;            // length of memory buffer
	unsigned interval;     // sleep for `interval` nsecs between memory actions
	unsigned count;        // perform memory action `count` times
#	ifdef SYN_MUTEX
		pthread_mutex_t mutex; // only one thread at time should access memory
#	endif
};
