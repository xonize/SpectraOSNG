#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/spectraos.kernel isodir/boot/spectraos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "spectraos" {
	multiboot2 /boot/spectraos.kernel
}
EOF
grub-mkrescue -o spectraos.iso isodir
