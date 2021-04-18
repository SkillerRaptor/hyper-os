#!/bin/sh

KERNEL_HDD=./build/Kernel.hdd

rm -r ./build
mkdir ./build
rm -f ../Kernel.hdd
rm -f $KERNEL_HDD
dd if=/dev/zero bs=1M count=0 seek=64 of=$KERNEL_HDD
parted -s $KERNEL_HDD mklabel msdos
parted -s $KERNEL_HDD mkpart primary 1 100%
$THIRD_PARTY_HOME/echfs/echfs-utils -m -p0 $KERNEL_HDD quick-format 32768
$THIRD_PARTY_HOME/echfs/echfs-utils -m -p0 $KERNEL_HDD import Kernel.elf Kernel.elf
$THIRD_PARTY_HOME/echfs/echfs-utils -m -p0 $KERNEL_HDD import limine.cfg limine.cfg
$THIRD_PARTY_HOME/echfs/echfs-utils -m -p0 $KERNEL_HDD import limine.sys limine.sys
$THIRD_PARTY_HOME/limine/bin/limine-install $KERNEL_HDD