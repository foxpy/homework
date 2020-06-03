#ifdef _WIN32
#	define _CRT_RAND_S
#endif

#if defined __linux__ || defined __ANDROID_API__
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
#	elif defined __ANDROID_API__
#		if __ANDROID_API__ < 28
			ret = arc4random();
#		else
			getrandom(&ret, sizeof(ret), 0);
#		endif
#	else
		ret = rand();
#	endif
	return ret;
}

uint64_t rnd64() {
	uint64_t ret = rnd32();
	ret <<= 32;
	ret |= rnd32();
	return ret;
}
