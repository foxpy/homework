#include <stdint.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "util.h"
#include "writer.h"
#define XORSHIFT8(x) {x ^= (x << 3); x ^= (x >> 1); x ^= (x << 4);}

void continious_writer(struct thread_data *args) {
	uint8_t *data = args->ptr;
	struct timespec rqtp = { 0, args->interval };
	uint8_t c = 17;
	for (unsigned count = 0; count != args->count; ++count) {
		XORSHIFT8(c);
		memset(data, (int) c, args->len);
		nanosleep(&rqtp, NULL);
	}
	pthread_exit(NULL);
}
