#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stddef.h>

/* The framebuffer I/O ports */
#define FRAMEBUFFER_COMMAND_PORT         0x3D4
#define FRAMEBUFFER_DATA_PORT            0x3D5

/* The I/O port commands */
#define FRAMEBUFFER_HIGH_BYTE_COMMAND    14
#define FRAMEBUFFER_LOW_BYTE_COMMAND     15

/* Output a byte of data to the provided IO port. */
void outb(uint16_t port, uint8_t data);

/* Retrieve a byte of data from the provided IO port. */
uint8_t inb(uint16_t port);

#endif
