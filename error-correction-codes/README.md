# error-correction-codes

This project holds various libraries and tools I have written for my course work.

Libraries:

- [util](util/doc.md) - small utility/math/io helpers
- [bit-array](bit-array/doc.md) - insanely slow, but memory efficient bit queue
(the name says it is array but it is actually a queue, I know I am smart).
This library is slow and is used everywhere. so almost every binary
in this project is insanely slow. My bad
- [bytes-to-string](bytes-to-string/doc.md) - small functions to format memory to bit/hex string,
actually not used in this project
- [cmdopts](cmdopts/doc.md) - my first attempt to write CLI arguments library,
works quite well but pretty tedious to use
- [ecc](ecc/doc.md) - a collection of some basic error correction facilities
- [noise-simulator](noise-simulator/doc.md) - actually good quality library,
simulates various types of line noise
- [random-generator](random-generator/doc.md) - cross-platform fast random functions
with support for integers and floating point
- [serial-emulator](serial-emulator/doc.md) - also a good quality library,
wraps bits into serial port representation (like what would be sent over RS-232 wire, for example)

Executables:

- [noisify](noisify.c#L12-L28) - consumes file/pipe and outputs damaged data,
damage is highly customizable
- [ecc-repetition](ecc-repetition.c#L14-L18) - basic ECC code, pretty inefficient
- [ecc-hamming](ecc-hamming.c#L13-L19) - basic ECC code, more efficient than previous one
- [ecc-interleaver](ecc-interleaver.c#L13-L21) - interleaver with configurable window size
- [error-count](error-count.c#L9-L10) - print number of different bits between two files
- [random-gen](random-gen.c#L12-L14) - outputs good quality (not crypto quality though) random
- [serial-wrap](serial-wrap.c#L12-L21) - (un)wraps data in serial port representation
