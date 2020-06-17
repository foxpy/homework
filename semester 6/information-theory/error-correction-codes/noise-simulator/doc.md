```c
#include "bit-array.h"
#include "noise.h"
```

Simulates line noise on bit array. Currently, only two types of noise
are implemented, but they are considered sufficient for any simulation:

- [Shot noise](https://en.wikipedia.org/wiki/Shot_noise). In other words,
a bit flip;
- [Burst noise](https://en.wikipedia.org/wiki/Burst_noise).

### noise_init_bit_flip()

```c
noise_t* noise_init_bit_flip(double frequency);
```

Returns a pointer to `noise_t` generator structure, which could be used
in future to apply shot noise. Should be freed with `noise_free()`
after usage. `frequency` means how much bits are going to be flipped:
`0.0` means no bit flips, `1.0` means every bit will be flipped, `0.5`
means every bit is flipped with probability of 50% (absolutely unusable
communication channel).
Returns `NULL` if `frequency` is out of `[0, 1)` range.

### noise_init_burst()

```c
noise_t* noise_init_burst(int type, double frequency, size_t mean_length, size_t length_st_dev);
```

A bit more complicated than previous one. Returns the same pointer to
generator structure which should also eventually be freed. `type` is
either `NOISE_BURST_UP` or `NOISE_BURST_DOWN`, which reflects how bits
are going to be damaged: up for all damaged bits set to 1, down - to 0.
`frequency` represents a probability of occuring a damaged bit sequence:
`0.0` stands for data absolutely unaffected by any noise, `1.0` means all
information is lost, `0.1` means for every bit out of damaged sequences
there is a probability of 10% for a new sequence to occur. `mean_length`
and `length_st_dev` specify how long the damaged sequences are going to
be (in bits): damaged sequence lengths are distributed normally.
Returns `NULL` if `frequency` is out of `[0, 1)` range, if supplied
`type` is wrong, or if `mean_length` equals zero.

### noise_free()

```c
void noise_free(noise_t *generator);
```
This function destroys `generator` and frees all associated resources.
Should be called on every `noise_t*` pointer obtained from
`noise_init_bit_flip()` and `noise_init_burst()` functions.

### noise_apply()

```c
size_t noise_apply(bits_t *dst, bits_t *src, noise_t *generator);
```

Moves all data from `src` to `dst`, using `generator` to apply noise
damage to it. Returns number of damaged bits.
