#!/bin/sh
# Full Compilation and Run - clean, config, build, iso, qemu
set -e
. ./clean.sh
. ./config.sh
. ./build.sh
. ./iso.sh
. ./qemu.sh