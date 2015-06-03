#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early(void)
{
    terminal_init();
}

void kernel_main(void)
{
    terminal_putstring("Hello!\n Welcome to kernel world.");
}

