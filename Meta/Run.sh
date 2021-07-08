#!/bin/bash

qemu-system-x86_64 \
  -drive file=nvme.img,if=none,id=NVME1,format=raw \
  -device nvme,drive=NVME1,serial=nvme \
  -drive file="$HYPEROS_BINARY_DIR/Root/boot/kernel.hdd",if=none,id=disk,format=raw \
  -device ahci,id=ahci \
  -device ide-hd,drive=disk,bus=ahci.0 \
  -drive file=usb.img,if=none,id=usbstick,format=raw \
  -usb \
  -vga std \
  -serial stdio \
  -m 256 \
  -enable-kvm \
  -smp 4
