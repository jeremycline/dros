# Entry point for the kernel as defined in the linker script.
.globl _start
.type _start, @function

# Multiboot specification so this is bootable by a compliant bootloader
# https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
.set MAGIC_NUMBER, 0x1BADB002
.set FLAGS, 0x0
.set CHECKSUM, -(MAGIC_NUMBER + FLAGS)

.set KERNEL_STACK_SIZE, 4096


.section .multiboot
    .align 4
    .long MAGIC_NUMBER
    .long FLAGS
    .long CHECKSUM


.section .text
    _start:
        # Set up the stack pointer and call the C entry point
        movl $stack_top, %esp
        call kernel_main

        cli
        hlt
        .Lhalt:
            jmp .Lhalt


.section .bss
    .align 4
    stack_bottom:
        .skip KERNEL_STACK_SIZE
    stack_top:
