#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom spectraos.iso -d int -D qemu_log.txt -M smm=off
