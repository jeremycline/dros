#include <stddef.h>
#include <string.h>
#include <stdio.h>

int printf(const char *restrict string, ...)
{
    putchar(string[0]);
    return 0;
}
