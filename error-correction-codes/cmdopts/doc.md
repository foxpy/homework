```c
#include "cmdopts.h"
```

This library implements a very simple parsing of command line arguments
of the following syntax:

```bash
./program --flag1 val1 --flag2 val2 pos1 pos2 pos3
```

Only positional arguments and `--key value` style flags are supported.
Flags are followed by positional arguments.

### opts_t

Holds internal representation of arguments,
should be only modified and accessed using the following functions:

### cmdopts_parse()

```c
void cmdopts_parse(opts_t *opts, int argc, char *argv[]);
```

Initializes `opts_t` object pointed to by `opts`
using standard command line arguments `argv` length of `argc`.
`opts_t` object should be destroyed using `cmdopts_free()`.

### cmdopts_free

```c
void cmdopts_free(opts_t *opts);
```

Destroys `opts_t` object pointed to by `opts`.
Double-free is undefined behaviour.

### cmdopts_num_posopts()

```c
int cmdopts_num_posopts(opts_t *opts);
```

Returns number of positional arguments.

### cmdopts_get_posopt()

```c
char* cmdopts_get_posopt(opts_t *opts, int n);
```

Returns pointer to positional argument `n`. Numeration starts from zero.
Accessing argument `cmdopts_num_posopts()` and greater is undefined behaviour.

### cmdopts_exists()

```c
bool cmdopts_exists(opts_t *opts, char *opt);
```

Returns `true` if requested flag is specified in command line arguments,
`false` otherwise.

### cmdopts_get_opt()

```c
char* cmdopts_get_opt(opts_t *opts, char *opt);
```

Returns pointer to value of key `opt`.
Warning: returned pointer may be a pointer to `NULL`.
It means that the specified flag does not have an argument, e.g.

```bash
./program --flag1 --flag2 val2
```

Such syntax should not be used and is considered as erratic.
Programs should check return value of `cmdopts_get_opt()` for `NULL`
and exit with syntax error in such case.

Accessing values of keys for which `cmdopts_exists()`
returns `false` is undefined behaviour.
