#include <stdio.h>
#ifdef _WIN32
#	include <io.h>
#	include <fcntl.h>
#endif
#include "util.h"

void reopen_binary_read(FILE *stream) {
#	ifdef _WIN32
		_setmode(_fileno(stream), _O_BINARY);
#	else
		freopen(NULL, "rb", stream);
#	endif
}

void reopen_binary_write(FILE *stream) {
#	ifdef _WIN32
		_setmode(_fileno(stream), _O_BINARY);
#	else
		freopen(NULL, "wb", stream);
#	endif
}
