#ifdef _WIN32
#	define _CRT_RAND_S
#endif

#ifdef __linux__
#	include <sys/random.h>
#endif

#include <stdlib.h>
#include <stdint.h>
#include "random.h"

uint32_t rnd32() {
	uint32_t ret;
#	ifdef _WIN32
		rand_s(&ret);
#	elif defined __linux__
		getrandom(&ret, sizeof(ret), 0);
#	else
		ret = rand();
#	endif
	return ret;
}
