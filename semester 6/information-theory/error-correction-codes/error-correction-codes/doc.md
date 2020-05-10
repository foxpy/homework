```c
#include repetition-code.h
```

### repetition_encode(), repetition_decode()

```c
void repetition_encode(bits_t *dst, bits_t *src);
void repetition_decode(bits_t *dst, bits_t *src);
```

Encodes and decodes `src` data to `dst` using
[repetition code](https://en.wikipedia.org/wiki/Repetition_code).
After completion, `src` is always emptied.
