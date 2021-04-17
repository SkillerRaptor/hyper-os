#!/bin/sh

KERNEL_ELF=../cmake-build-debug/Kernel/Kernel.elf

objdump $KERNEL_ELF -dS -Mintel