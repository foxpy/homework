#pragma once
struct thread_data {
	void *ptr;
	size_t len;
	unsigned interval;
	unsigned count;
};
