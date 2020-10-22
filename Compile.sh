#!/bin/sh

i686-elf-as boot.s -o boot.o
i686-elf-g++ -c kernel.cpp -mno-red-zone -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
qemu-system-i386 -kernel myos.bin