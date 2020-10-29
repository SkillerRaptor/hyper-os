#!/bin/sh

qemu-system-i386 \
    -m 128 \
    -d int,cpu_reset,guest_errors \
    -no-reboot \
    -no-shutdown \
    -kernel ../HyperOS.bin