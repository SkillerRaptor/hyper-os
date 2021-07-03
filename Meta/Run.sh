#!/bin/bash

qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file="$HYPEROS_BINARY_DIR/Root/boot/kernel.hdd" -serial stdio -m 256 -soundhw pcspk -enable-kvm -smp 4
