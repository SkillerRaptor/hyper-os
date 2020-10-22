#!/bin/sh

qemu-system-i386 \
    -m 128 \
    -d cpu_reset,guest_errors \
    -kernel ../HyperOS.bin