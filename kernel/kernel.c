#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <tty.h>

void kernel_main(void)
{
    fb_init();
    char *hi = "Hello!\nWelcome to kernel world.";
    fb_write(hi, strlen(hi));
}
