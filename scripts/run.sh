#!/bin/sh

qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=../kernel.hdd -serial stdio -m 256 -soundhw pcspk