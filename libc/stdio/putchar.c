#include <stdio.h>

#if defined(__is_dros_kernel)
#include <kernel/tty.h>
#endif

int putchar(int character)
{
#if defined(__is_dros_kernel)
    char input = (char) character;
    fb_writechar(input);
#else
    /* TODO: Implement a system call */
#endif

    return character;
}
