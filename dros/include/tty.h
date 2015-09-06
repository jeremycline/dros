#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/* Initialize the terminal */
void fb_init(void);

/* Set the frame buffer colors */
void fb_set_color(enum vga_color, enum vga_color);

/* Write to an arbitrary cell */
void fb_write_cell(char, enum vga_color, 
        enum vga_color, size_t , size_t)
/* Write a single character to the terminal */
void fb_write_char(char c);

/* Write non-null terminated data to the terminal */
void fb_write(const char *data, size_t length);

#endif
