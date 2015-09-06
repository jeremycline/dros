#include <stdlib.h>
#include <stdio.h>

__attribute__((__noreturn__))
void abort(void)
{
    printf("Kernel panic. Hopefully you have your towel.\n");
    while(1) { }
    __builtin_unreachable();
}
