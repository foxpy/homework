```c
#include "hamming-code.h"

### hamming_decode(), hamming_encode()

```c
void hamming_encode(bits_t *dst, bits_t *src);
void hamming_decode(bits_t *dst, bits_t *src);
```

Encodes and decodes `src` data to `dst` using
[Hamming code](https://en.wikipedia.org/wiki/Hamming(7,4)).
After completion, `src` is always emptied.
Length of `src` should be divisible by 4.
