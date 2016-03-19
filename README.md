# The Truly Dreadful Operating System

Do you feel that your life is just too easy? Are you tired of software that Just® Works™?
If so, you are in the right place. Written by someone who has no experience with kernel 
development and only a basic understanding of C, this operating system almost certainly does not
do what you want it to do.

## Build instructions
```
vagrant up
vagrant ssh
cd devel/dros
./build.sh
qemu-system-i386 -kernel kernel.elf
```

## Helpful tricks
QEMU has the ability to work with GDB (which is not in the least bit dreadful). You can instruct
QEMU to start the guest and wait for a remote debugger to attach and continue the execution:
```
$ qemu-system-i386 -s -S -kernel kernel.elf
$ gdb
(gdb) target remote localhost:1234
```
There is a very good guide for GDB at http://www.dirac.org/linux/gdb/.

## Layout
A brief description of the repository layout.

### kernel

Contains generic kernel code.

### arch

Contains the architecture specific code. This includes some assembly which acts
as an entry point for the kernel and calls the generic kernel main function.


### freestanding

GCC requires that a freestanding environment provide the following functions:

 * `memcpy`
 * `memmove`
 * `memset`
 * `memcmp`
 * `abort` (if `__builtin_trap` is used and the target does not implement the
   `trap` pattern).

This requirement is stated in Section 2.1 of the GCC User Manual (for GCC 5.3).
These functions are provided by the `string.h` and `stdlib.h` standard library
interfaces. Although these functions are defined in the libc implementation, 
they are duplicated here using kernel methods rather than system calls.

In addition to the required methods above, additional methods are implemented
for the sake of convenience.
