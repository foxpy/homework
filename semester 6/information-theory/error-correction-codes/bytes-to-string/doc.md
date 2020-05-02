```c
#include "bytes-to-string.h"
```

### bytes_to_bitstring()

```c
void bytes_to_bitstring(void *dst, void *src, size_t len);
```

Formats `src` bytes length of `len` to bit string representation written to `dst`.
`dst` should be large enough to hold `8*src+1` bytes of data.

### bytes_to_hexstring()

```c
void bytes_to_hexstring(void 8dst, void *src, size_t len);
```

Formats `src` bytes length of `len` to hex string representation written to `dst`.
`dst` should be large enough to hold `2*src+1` bytes of data.
