#!/bin/bash

script_path="$(dirname "$(realpath "$0")")"
boot_path=$script_path/../../Boot

qemu-system-x86_64 \
  -drive file=$boot_path/nvme.img,if=none,id=NVME1,format=raw \
  -device nvme,drive=NVME1,serial=nvme \
  -drive file=$boot_path/HyperOS.iso,if=none,id=disk,format=raw \
  -device ahci,id=ahci \
  -device ide-hd,drive=disk,bus=ahci.0 \
  -drive file=$boot_path/usb.img,if=none,id=usbstick,format=raw \
  -usb \
  -vga std \
  -serial stdio \
  -m 512 \
  -smp 1 \
  -d int,cpu_reset \
  -no-shutdown \
  -no-reboot
