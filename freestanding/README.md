freestanding
------------

GCC requires that a freestanding environment provide the following functions:

 * `memcpy`
 * `memmove`
 * `memset`
 * `memcmp`
 * `abort` (if `__builtin_trap` is used and the target does not implement the
   `trap` pattern).

This requirement is stated in Section 2.1 of the GCC User Manual (for GCC 5.3).
These functions are provided by the `string.h` except for `abort` which is from
`stdlib.h`. Although these functions are defined in the libc implementation, they
are duplicated here. This is not ideal, but is a simple solution for the present.
