```c
#include "bit-array.h"
```

This library provides `bits_t` object with several functions defined,
e.g. pushing bit to front/back and popping bit from front/back.

### bits_t

Should be initialized by `bitarray_alloc()` before using
and freed by `bitarray_free()` in the end.

### bitarray_alloc()

```c
void bitarray_alloc(bits_t *bits);
```

Initializes `bits_t` object pointed to by `bits`.
Blows up the whole program on memory allocation failure.

### bitarray_free()

```c
void bitarray_free(bits_t *bits);
```

Destroys `bits_t` object pointed to by `bits`.
Double free is undefined behaviour.

### bitarray_copy()

```c
void bitarray_copy(bits_t *dst, bits_t *src);
```

Initializes new `bits_t` object `dst` from `src`, copying data and allocating memory.

### bitarray_clear()

```c
void bitarray_clear(bits_t *bits);
```

Empties, but not destroys, `bits` object.

### bitarray_fill_from_memory()

```c
void bitarray_fill_from_memory(bits_t *dst, void *src, size_t nbits);
```

Given pointer `src` to memory, fills `dst` object with `nbits` bits in sequential order.

### bitarray_to_memory()

```c
void* bitarray_to_memory(bits_t *src, size_t *nbits);
```

Returns pointer to allocated memory storing bits copied from `src`.
This memory should be freed via `free()` stdlib function.
Stores number of copied bits in `nbits`.
Unset bits are zeroed out.
Destroys (frees) `src`.

### bitarray_size()

```c
size_t bitarray_size(bits_t *bits);
```

Returns the number of bits stored in `bits_t` object pointed to by `bits`.

### bitarray_empty()

```c
bool bitarray_empty(bits_t *bits);
```

Returns `true` is pointed object does not store any bits,
`false` otherwise.

### push/pop back/front functions

```c
void bitarray_push_front(bits_t *bits, bit b);
void bitarray_push_back(bits_t *bits, bit b);
void bitarray_pop_front(bits_t *bits);
void bitarray_pop_back(bits_t *bits);
```

Function names are self-explanatory.
Popping from `bits_t` object for which `bitarray_empty()` returns `true`
is undefined behaviour.

### bitarray_front()

```c
bit bitarray_front(bits_t *bits);
```

Returns first bit stored.
Accessing first bit of `bits_t` object for which `bitarray_empty()`
returns `true` is undefined behaviour.

### bitarray_back()

```c
bit bitarray_back(bits_t *bits);
```

Returns last bit stored.
Accessing last bit of `bits_t` object for which `bitarray_empty()`
returns `true` is undefined behaviour.
