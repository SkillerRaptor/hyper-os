#!/bin/bash

script_path="$(dirname "$(realpath "$0")")"
boot_path=$script_path/../../Boot

dd if=/dev/zero bs=1M count=0 seek=128 of=$boot_path/nvme.img
dd if=/dev/zero bs=1M count=0 seek=128 of=$boot_path/usb.img

rm $boot_path/HyperOS.iso

xorriso \
  -as mkisofs \
  -b limine-cd.bin \
  -no-emul-boot \
  -boot-load-size 4 \
  -boot-info-table \
  --efi-boot limine-eltorito-efi.bin \
  -efi-boot-part \
  --efi-boot-image \
  --protective-msdos-label $boot_path \
  -o $boot_path/HyperOS.iso

$boot_path/limine-install-linux-x86_64 $boot_path/HyperOS.iso
