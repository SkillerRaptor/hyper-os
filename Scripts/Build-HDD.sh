#!/bin/sh

KERNEL_HDD=../Kernel.hdd
THIRD_PARTY_PATH=../../ThirdParty

rm -f $KERNEL_HDD
dd if=/dev/zero bs=1M count=0 seek=64 of=$KERNEL_HDD
parted -s $KERNEL_HDD mklabel msdos
parted -s $KERNEL_HDD mkpart primary 1 100%
$THIRD_PARTY_PATH/echfs/echfs-utils -m -p0 $KERNEL_HDD quick-format 32768
$THIRD_PARTY_PATH/echfs/echfs-utils -m -p0 $KERNEL_HDD import Kernel.elf Kernel.elf
$THIRD_PARTY_PATH/echfs/echfs-utils -m -p0 $KERNEL_HDD import limine.cfg limine.cfg
$THIRD_PARTY_PATH/echfs/echfs-utils -m -p0 $KERNEL_HDD import $THIRD_PARTY_PATH/limine/limine.sys limine.sys
$THIRD_PARTY_PATH/limine/limine-install-linux-x86_64 $KERNEL_HDD
