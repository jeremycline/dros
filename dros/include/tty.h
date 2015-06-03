#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/* Initialize the terminal */
void terminal_init(void);

/* Write a single character to the terminal */
void terminal_putchar(char c);

/* Write non-null terminated data to the terminal */
void terminal_putdata(const char *data, size_t length);

/* Write a null terminated string to the terminal */
void terminal_putstring(const char *string); 

#endif
