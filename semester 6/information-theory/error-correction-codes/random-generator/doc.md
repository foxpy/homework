```c
#include "random.h"
```

Implements [xorshift64 PRNG](https://www.jstatsoft.org/article/view/v008i14).
Uses high quality random for seeding on these platforms:
- Windows
- Linux
- Android

Seeding does not work on other platforms.

### rnd_state_t

Holds state for PRNG. Should be seeded with `rnd_init()` before using.

### rnd_init

```c
void rnd_init(rnd_state_t *state);
```

Seeds `state` with cryptographic quality random bytes on supported platforms.
Seeds with all zeroes on unsupported platforms.

### rnd8(), rnd16(), rnd32(), rnd64()

```c
uint8_t rnd8(rnd_state_t *state);
uint16_t rnd16(rnd_state_t *state);
uint32_t rnd32(rnd_state_t *state);
uint64_t rnd64(rnd_state_t *state);
```

Returns 8/16/32/64 bits of random using xorshift output seeded by `state`.

### rnd_fp64(), rnd_fp32()

```c
double rnd_fp64(rnd_state_t *state);
float rnd_fp32(rnd_state_t *state);
```

Returns random floating point value in range `[0.0, 1.0)`.
