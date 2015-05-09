OBJECTS = loader.o kernel.o
CC = ~/opt/cross/bin/i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -nostdlib -lgcc -Wall -Wextra -Werror
LDFLAGS = -T link.ld
AS = ~/opt/cross/bin/i686-elf-as
ASFLAGS = --warn --fatal-warnings

kernel.elf : $(OBJECTS)
	$(CC) $(LDFLAGS) -o kernel.elf $(OBJECTS) $(CFLAGS)

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
	rm -rf *.o kernel.elf os.iso iso run.log
