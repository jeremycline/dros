DESTDIR=$(PWD)/sysroot
PREFIX=/usr/local
LIBDIR=$(PREFIX)/lib
INCLUDEDIR=$(PREFIX)/include

CC = ~/opt/cross/bin/i686-elf-gcc
AR = ~/opt/cross/bin/i686-elf-ar
CFLAGS := -g -std=gnu11 -Wall -Wextra -Werror --sysroot=$(DESTDIR) -I$(DESTDIR)$(INCLUDEDIR)
LIBK_CFLAGS := $(CFLAGS) -ffreestanding -fbuiltin
AS = ~/opt/cross/bin/i686-elf-as
ASFLAGS = --warn --fatal-warnings
LIBS = -nostdlib -lgcc

# These objects do not have dependencies on the kernel
FREESTANDING_OBJECTS := \
	stdio/printf.o \
	stdio/putchar.o \
	stdio/puts.o \
	stdlib/abort.o \
	string/memcmp.o \
	string/memcpy.o \
	string/memmove.o \
	string/memset.o \
	string/strlen.o \

# These objects require kernel system calls to work
HOSTED_OBJECTS := \

OBJECTS := \
	$(FREESTANDING_OBJECTS) \
	$(HOSTED_OBJECTS)

LIBK_OBJECTS := $(FREESTANDING_OBJECTS:.o=.libk.o)

BINARIES = libc.a libk.a

%.o: %.c install-headers
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s install-headers
	$(AS) $(ASFLAGS) $< -o $@

%.libk.o: %.c
	$(CC) $(LIBK_CFLAGS) -c $< -o $@

%.libk.o: %.s
	$(AS) $(LIBK_ASFLAGS) $< -o $@

.PHONY: all install-headers install-libs clean

all: $(BINARIES)

libc.a: $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

libk.a: $(LIBK_OBJECTS)
	$(AR) rcs $@ $(LIBK_OBJECTS)

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -RTv include $(DESTDIR)$(INCLUDEDIR)

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

clean:
	rm -f $(BINARIES) $(OBJECTS) $(LIBK_OBJECTS)
	rm -rf $(DESTDIR)
