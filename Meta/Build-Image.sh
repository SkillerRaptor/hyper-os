#!/bin/bash

KERNEL_HDD=$HYPEROS_BINARY_DIR/Root/boot/kernel.hdd
ECHFS_COMMAND=$HYPEROS_SOURCE_DIR/ThirdParty/echfs/echfs-utils
LIMINE_INSTALL_COMMAND=$HYPEROS_SOURCE_DIR/ThirdParty/limine/limine-install-linux-$HYPEROS_ARCH

rm -f "$KERNEL_HDD"
dd if=/dev/zero bs=1M count=0 seek=64 of="$KERNEL_HDD"
parted -s "$KERNEL_HDD" mklabel msdos
parted -s "$KERNEL_HDD" mkpart primary 1 100%
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" quick-format 32768
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" import "$HYPEROS_BINARY_DIR/Root/boot/kernel" kernel
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" import "$HYPEROS_BINARY_DIR/Root/boot/limine.cfg" limine.cfg
"$ECHFS_COMMAND" -m -p0 "$KERNEL_HDD" import "$HYPEROS_SOURCE_DIR/ThirdParty/limine/limine.sys" limine.sys
"$LIMINE_INSTALL_COMMAND" "$KERNEL_HDD"
