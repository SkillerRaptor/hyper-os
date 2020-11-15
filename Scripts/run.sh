#!/bin/sh

qemu-system-x86_64 \
    -m 2G \
    -d int,cpu_reset,guest_errors \
    -drive format=raw,media=disk,index=0,file=../build/HyperOS.hdd \
    -monitor stdio \
    -no-reboot \
    -no-shutdown