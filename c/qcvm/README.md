
# QCVM

Here is a work-in-progress rewrite of [QCVM](https://github.com/erysdren/QCVM).

I tried to make use of no compiler-specific features, but it has not been
extensively tested on other platforms yet.

- GCC flags: `-std=c89 -pedantic -Wextra -Wall -Werror`
- Clang flags: `-std=c89 -pedantic -Wextra -Wall -Werror`

**NOTE**: Only supports vanilla QCVM opcodes and has only been tested with the
[FTEQCC](https://www.fteqcc.org/) compiler.

## Assumptions

In the interest of not including any libc headers, it makes several assumptions
about the environment it will be running in:

- `int` is 4 bytes
- `short` is 2 bytes
- `char` is 1 byte
