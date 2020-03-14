#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "util.h"
#include "writer.h"
#include "reader.h"

#define BUFFER_SIZE 16
#define ITERATIONS 32

int main(void) {
	uint8_t *data = (uint8_t*) malloc(BUFFER_SIZE);
	struct thread_data args = { data, BUFFER_SIZE, 1000, ITERATIONS };
	pthread_t threads[2];

	pthread_create(&threads[0], NULL, (void*) continious_writer, &args);
	pthread_create(&threads[1], NULL, (void*) continious_reader, &args);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	return EXIT_SUCCESS;
}
