#!/bin/sh
set -e
. ./headers.sh
cp font.o kernel/arch/x86_64/font.o
for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
