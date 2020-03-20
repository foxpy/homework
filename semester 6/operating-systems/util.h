#pragma once
struct thread_data {
	void *ptr;         // size of memory buffer
	size_t len;        // length of memory buffer
	unsigned interval; // perform memory action every `interval` nanoseconds
	unsigned count;    // perform memory action `count` times
};
