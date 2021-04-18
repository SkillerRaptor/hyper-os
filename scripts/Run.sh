#!/bin/sh

KERNEL_HDD=../cmake-build-debug/Kernel/build/Kernel.hdd
qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=../Kernel.hdd -serial stdio -m 256 -soundhw pcspk