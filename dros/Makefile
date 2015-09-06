DESTDIR=$(PWD)/sysroot
PREFIX=/usr
BOOTDIR=/boot
LIBDIR=$(PREFIX)/lib
INCLUDEDIR=$(PREFIX)/include

ARCHDIR := arch/i386
include $(ARCHDIR)/make.config

CC = ~/opt/cross/bin/i686-elf-gcc --sysroot=$(DESTDIR)
CFLAGS := -g -std=gnu11 -ffreestanding -fbuiltin -Wall \
	-Wextra -Werror $(KERNEL_ARCH_CFLAGS)
LDFLAGS := $(KERNEL_ARCH_LDFLAGS)
AS = ~/opt/cross/bin/i686-elf-as
ASFLAGS = --warn --fatal-warnings
LIBS = -nostdlib -lgcc $(KERNEL_ARCH_LIBS)

CRTI_OBJECT := $(ARCHDIR)/crti.o
CRTBEGIN_OBJECT := $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJECT := $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJECT := $(ARCHDIR)/crtn.o

OBJECTS := \
	$(KERNEL_ARCH_OBJECTS) \
	kernel/kernel.o

OUR_OBJECTS := \
	$(CRTI_OBJECT) \
	$(OBJECTS) \
	$(CRTN_OBJECT)

LINK_OBJECTS := \
	$(CRTI_OBJECT) \
	$(CRTBEGIN_OBJECT) \
	$(OBJECTS) \
	$(CRTEND_OBJECT) \
	$(CRTN_OBJECT)

# Run with -c to stop the linker running
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY: all install-headers install-kernel clean

all : install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)

install-kernel: kernel.elf
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp kernel.elf $(DESTDIR)$(BOOTDIR)

kernel.elf : $(LINK_OBJECTS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o kernel.elf $(LINK_OBJECTS) $(CFLAGS) $(LIBS)

clean:
	rm -rf iso
	rm $(OUR_OBJECTS) kernel.elf
