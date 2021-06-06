#!/bin/sh

BASEDIR=$(dirname "$0")
cd "$BASEDIR"/.. || exit

qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=./Build/Kernel.hdd -d int,cpu_reset -serial stdio -no-reboot -no-shutdown -m 256 -enable-kvm -smp 4
