```c
#include "noise.h"
```

### enum noise_t

Describes type of noise applied:

`NOISE_BIT_FLIP` - a single bit is flipped.

`NOISE_LINEAR` - a sequence of bits is flipped.

### union noise_cfg_t

Hold different structures for different types of noise applied.

All possible usage cases described:

For `NOISE_BIT_FLIP`:

`noise_config.bit_flip.num_bit_flips = size_t;` - number of random bits flipped in the message.

For `NOISE_LINEAR`:

`noise_config.linear.damage_length = size_t` - sequence length of flipped bits.

### apply_noise()

```c
void apply_noise(void *ptr, size_t len, noise_t ntype, noise_conf_t nconfig);
```

Applies `ntype` noise to `ptr` bytes length of `len`. Noise simulator settings are passed in `nconfig`.
