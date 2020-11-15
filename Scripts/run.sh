#!/bin/sh

qemu-system-x86_64 \
    -m 2G \
    -d int,cpu_reset,guest_errors \
    -monitor stdio \
    -no-reboot \
    -no-shutdown \
    -hda ../build/HyperOS.hdd