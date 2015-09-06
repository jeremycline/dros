export DESTDIR:=$(PWD)/sysroot

BUILD_SUBDIRS = libc
.PHONY: all run clean build_subdirs $(BUILD_SUBDIRS)

build_subdirs: $(BUILD_SUBDIRS)

all: build_subdirs os.iso

$(BUILD_SUBDIRS):
	$(MAKE) -C $@

os.iso: build_subdirs
	mkdir -p iso/boot/grub/
	cat > iso/boot/grub/grub.cfg << EOF
	menuentry "dros" {
	multiboot /bin/boot/kernel.elf
	}
	EOF
	cp kernel.elf iso/boot/kernel.elf
	grub2-mkrescue -o os.iso iso

run: os.iso
	qemu-system-i386  -m 32 \
						-display sdl \
						-D run.log \
						-d guest_errors \
						-boot d \
						-cdrom os.iso

clean:
	rm -rfv iso sysroot
	rm -v os.iso run.log
