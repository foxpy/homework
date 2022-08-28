```c
#include "interleaver.h"
```

Interleaver shuffles ecc-encoded data so it better stands against burst errors.
Read more [here](https://en.wikipedia.org/wiki/Error_correction_code#Interleaving).

### interleaver_t

Structure which holds internal state of interleaver.
Users of this library are expected to operate only with
pointers to this structure.

### interleaver_init()

```c
interleaver_t* interleaver_init(int type, size_t length, size_t width);
```

Initializes interleaver state, allocates all resources and returns
pointer to state. After usage, this state should be freed via call
to `interleaver_free()`.
`type` shouuld be either `INTERLEAVER_ENCODE` or `INTERLEAVER_DECODE`.
`length` and `width` improve interleaving capabilities (the more the better)
but increase latency, so these values must be choosed wisely.
For example, if packet transmission size is 16, it is wise
to use `length = 2` and `width = 8` or `length = 4` and `width = 4`.
`length` represents bytes and should be in range `[1, 65536)`.
`width` represents bytes and should be in range `[2, 65536)`.

### interleaver_free()

```c
void interleaver_free(interleaver_t *state);
```

Destroys passed interleaver state and frees all allocated resources.

### interleaver_process_data()

```c
void interleaver_process_data(bits_t *dst, bits_t *src, interleaver_t *state);
```

Moves data from `src` to `dst`, applying (de)interleaving to it
according to `state`.
