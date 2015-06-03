CFLAGS?=-O2 -g

OBJECTS = loader.o kernel.o
CC = ~/opt/cross/bin/i686-elf-gcc
CFLAGS:=$(CFLAGS) -std=gnu11 -ffreestanding -fbuiltin -Wall -Wextra -Werror
LDFLAGS = -T link.ld
AS = ~/opt/cross/bin/i686-elf-as
ASFLAGS = --warn --fatal-warnings
LIBS = -nostdlib -lgcc

kernel.elf : $(OBJECTS)
	$(CC) $(LDFLAGS) -o kernel.elf $(OBJECTS) $(CFLAGS) $(LIBS)

os.iso: kernel.elf
	mkdir -p iso/boot/grub/
	cp grub.cfg iso/boot/grub/grub.cfg
	cp kernel.elf iso/boot/kernel.elf
	grub2-mkrescue -o os.iso iso

run: os.iso
	qemu-system-i386  -m 32 \
						-display sdl \
						-D run.log \
						-d guest_errors \
						-boot d \
						-cdrom os.iso

# Run with -c to stop the linker running
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf iso
	rm *.o kernel.elf os.iso run.log
