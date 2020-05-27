```c
#include "hamming-code.h"

### hamming_encode()

```c
void hamming_encode(bits_t *dst, bits_t *src);
```

Encodes `src` data to `dst` using
[Hamming code](https://en.wikipedia.org/wiki/Hamming(7,4)).
If there are insufficient (less than 4) bits left in `src`,
they are left unchanged.

### hamming_decode()

```c
size_t hamming_decode(bits_t *dst, bits_t *src);
```

Decodes `src` data to `dst` using
[Hamming code](https://en.wikipedia.org/wiki/Hamming(7,4)).
If there are insufficient (less than 8) bits left in `src`,
they are left unchanged.
