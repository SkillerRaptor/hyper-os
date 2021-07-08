#!/bin/bash

KERNEL_HDD=$HYPEROS_BINARY_DIR/Root/boot/kernel.hdd
NVME_IMG=$HYPEROS_BINARY_DIR/Root/boot/nvme.img
USB_IMG=$HYPEROS_BINARY_DIR/Root/boot/usb.img
ECHFS_COMMAND=$HYPEROS_SOURCE_DIR/ThirdParty/echfs/echfs-utils
LIMINE_INSTALL_COMMAND=$HYPEROS_SOURCE_DIR/ThirdParty/limine/limine-install-linux-x86_64

rm -f "$KERNEL_HDD" "$NVME_IMG" "$USB_IMG"
dd if=/dev/zero bs=1M count=0 seek=64 of="$KERNEL_HDD"
dd if=/dev/zero bs=1M count=0 seek=128 of="$NVME_IMG"
dd if=/dev/zero bs=1M count=0 seek=128 of="$USB_IMG"
parted -s "$KERNEL_HDD" mklabel msdos
parted -s "$KERNEL_HDD" mkpart primary 1 100%
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" quick-format 32768
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" import "$HYPEROS_BINARY_DIR/Root/boot/kernel" kernel
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" import "$HYPEROS_BINARY_DIR/Root/boot/limine.cfg" limine.cfg
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" import "$HYPEROS_SOURCE_DIR/ThirdParty/limine/limine.sys" limine.sys
"$LIMINE_INSTALL_COMMAND" "$KERNEL_HDD"
