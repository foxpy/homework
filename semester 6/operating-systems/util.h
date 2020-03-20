#pragma once
struct thread_data {
	void *ptr;         // size of memory buffer
	size_t len;        // length of memory buffer
	unsigned interval; // sleep for `interval` nsecs between memory actions
	unsigned count;    // perform memory action `count` times
};
