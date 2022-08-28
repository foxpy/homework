```c
#include "util.h"
```

Various helpful utility functions and macro.

### MAX(), MIN()

```c
MAX(a, b)
MIN(a, b)
```

Classic maximum/minimum macro.

### emalloc(), erealloc()

```c
void* emalloc(size_t size);
void* erealloc(void *ptr, size_t size);
```

Wrappers over stdlib `malloc()` and `realloc()`.
They simply crash the whole program if allocation fails.

### reopen_binary_read(), reopen_binary_write()

```c
void reopen_binary_read(FILE *stream);
void reopen_binary_write(FILE *stream);
```

These functions reopen given file stream in binary+read and
binary+write modes respectively. Useful when writing binary data
to `stdout`, `stderr`, etc.

### gcd(), lcm()

```c
unsigned gcd(unsigned a, unsigned b);
unsigned lcm(unsigned a, unsigned b);
```

Calculate Greatest Common Divisor and Least Common Multiple respectively.
