# Nuke built-in rules and variables.
override MAKEFLAGS += -rR
export SP_SYSROOT=$(shell pwd)/sysroot

override IMAGE_NAME := spectraos
export HEADERSDIR=$(SP_SYSROOT)/usr/include/
export LIBSDIR=$(SP_SYSROOT)/usr/lib/
export INCDIR=/usr/include/

export OS_CC=x86_64-elf-gcc --sysroot=$(SP_SYSROOT) -isystem=$(INCDIR)

# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

# Compiler for building the 'limine' executable for the host.
override DEFAULT_HOST_CC := x86_64-elf-gcc
$(eval $(call DEFAULT_VAR,HOST_CC,$(DEFAULT_HOST_CC)))

.PHONY: all
all: $(IMAGE_NAME).iso

.PHONY: all-hdd
all-hdd: $(IMAGE_NAME).hdd

.PHONY: run
run: $(IMAGE_NAME).iso
	# qemu-system-x86_64 -M q35 -m 2G -name SpectraOS -cdrom $(IMAGE_NAME).iso -boot d -monitor stdio -serial stdio
	qemu-system-x86_64 -D ./log.txt -d int -M q35 -m 2G -name SpectraOS -cdrom $(IMAGE_NAME).iso -boot d -serial stdio -M smm=off

.PHONY: run-uefi
run-uefi: ovmf $(IMAGE_NAME).iso
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf/OVMF.fd -cdrom $(IMAGE_NAME).iso -boot d

.PHONY: run-hdd
run-hdd: $(IMAGE_NAME).hdd
	qemu-system-x86_64 -M q35 -m 2G -hda $(IMAGE_NAME).hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf $(IMAGE_NAME).hdd
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf/OVMF.fd -hda $(IMAGE_NAME).hdd

ovmf:
	mkdir -p ovmf
	cd ovmf && curl -Lo OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1
	unset CC; unset CFLAGS; unset CPPFLAGS; unset LDFLAGS; unset LIBS; $(MAKE) -C limine CC="$(HOST_CC)"

.PHONY: headers libk i-libs kernel 
kernel: headers
	$(MAKE) -C kernel

libk:
	$(MAKE) -C libc

headers:
	mkdir -p sysroot
	mkdir -p sysroot/usr
	mkdir -p sysroot/usr/include
	mkdir -p sysroot/usr/lib
	mkdir -p sysroot/boot
	$(MAKE) -C kernel install-headers
	$(MAKE) -C libc install-headers

i-libs:
	$(MAKE) -C libc install-libs


$(IMAGE_NAME).iso: headers limine libk i-libs kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp -v kernel/kernel.elf \
		limine.cfg limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/
	mkdir -p iso_root/EFI/BOOT
	cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
	cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/
	xorriso -as mkisofs -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(IMAGE_NAME).iso
	./limine/limine bios-install $(IMAGE_NAME).iso
	rm -rf iso_root

$(IMAGE_NAME).hdd: limine kernel
	rm -f $(IMAGE_NAME).hdd
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(IMAGE_NAME).hdd
	sgdisk $(IMAGE_NAME).hdd -n 1:2048 -t 1:ef00
	./limine/limine bios-install $(IMAGE_NAME).hdd
	mformat -i $(IMAGE_NAME).hdd@@1M
	mmd -i $(IMAGE_NAME).hdd@@1M ::/EFI ::/EFI/BOOT
	mcopy -i $(IMAGE_NAME).hdd@@1M kernel/kernel.elf limine.cfg limine/limine-bios.sys ::/
	mcopy -i $(IMAGE_NAME).hdd@@1M limine/BOOTX64.EFI ::/EFI/BOOT
	mcopy -i $(IMAGE_NAME).hdd@@1M limine/BOOTIA32.EFI ::/EFI/BOOT

.PHONY: clean
clean:
	rm -rf iso_root $(IMAGE_NAME).iso $(IMAGE_NAME).hdd
	rm -rf sysroot
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf
	$(MAKE) -C kernel distclean