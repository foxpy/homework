#pragma once
#include <stdio.h>

#ifdef _WIN32
#	include <io.h>
#	include <fcntl.h>
#	define REOPEN_BINARY_READ(stream) { _setmode(_fileno(stream), _O_BINARY); }
#	define REOPEN_BINARY_WRITE(stream) { _setmode(_fileno(stream), _O_BINARY); }
#else
#	define REOPEN_BINARY_READ(stream) { freopen(NULL, "rb", stream); }
#	define REOPEN_BINARY_WRITE(stream) { freopen(NULL, "wb", stream); }
#endif
