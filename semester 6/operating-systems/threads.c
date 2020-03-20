#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "util.h"
#include "writer.h"
#include "reader.h"

#define BUFFER_SIZE 0x100000
#define ITERATIONS 64
#define SLEEP_INTERVAL_NSECS 10000

int main(void) {
	uint8_t *data = (uint8_t*) calloc(BUFFER_SIZE, sizeof(uint8_t));
	struct thread_data args = {
		data,
		BUFFER_SIZE,
		SLEEP_INTERVAL_NSECS,
		ITERATIONS,
	};
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, (void*) continious_writer, &args);
	pthread_create(&threads[1], NULL, (void*) continious_reader, &args);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	free(data);
	return EXIT_SUCCESS;
}
