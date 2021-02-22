#!/bin/sh

qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=./HyperOS.hdd -d int,cpu_reset,guest_errors -serial stdio -no-reboot -no-shutdown -m 2G
