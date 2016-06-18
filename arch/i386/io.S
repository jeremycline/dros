# Implementation of the kernel's io.h outb function using the cdecl calling
# convension.
.globl outb
.type outb, @function

# Implementation of the kernel's io.h inb function using the cdecl calling
# convension.
.globl inb
.type inb, @function

.section .text
    # Output a single byte to the given port.
    #
    # Stack layout:
    #   8(%esp) data byte
    #   4(%esp) port address (16 bits)
    outb:
        # Store the data byte in the `al` register
        movb 8(%esp), %al
        # Store the port address in the `dx` register
        movw 4(%esp), %dx
        # Push the byte in `al` out to the port in `dx`
        out %al, %dx
        ret

    # Read a single byte from the given port.
    #
    # Stack layout:
    #   4(%esp) port address (16 bits)
    inb:
        movw 4(%esp), %dx
        in %dx, %al
        leave
        ret
