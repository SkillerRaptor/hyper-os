#!/bin/sh

rm -f HyperOS.hdd

dd if=/dev/zero bs=1M count=0 seek=64 of=./HyperOS.hdd

parted -s ./HyperOS.hdd mklabel msdos
parted -s ./HyperOS.hdd mkpart primary 1 100%
parted -s ./HyperOS.hdd set 1 boot on

echfs-utils -m -p0 ./HyperOS.hdd quick-format 32768
echfs-utils -m -p0 ./HyperOS.hdd import ./Kernel/Kernel HyperOS.elf
echfs-utils -m -p0 ./HyperOS.hdd import ./limine.cfg limine.cfg

limine-install ./limine.bin ./HyperOS.hdd