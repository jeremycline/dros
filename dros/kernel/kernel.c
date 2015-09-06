#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early(void)
{
    /* TODO set up serial console and start logging */
    fb_init();
}

void kernel_main(void)
{
    char *hi = "Hello!\n Welcome to kernel world.";
    fb_write(hi, strlen(hi));
}

