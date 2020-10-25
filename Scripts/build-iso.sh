#!/bin/sh

sh ./build.sh

printf "\n\e[93m === Starting Building ISO === \e[39m\n"

cd ..
mkdir -p iso/boot/grub
cd iso/boot/grub
printf 'menuentry "HyperOS" {\n    multiboot /boot/HyperOS.bin\n}' > grub.cfg
cd ../../..
cp HyperOS.bin iso/boot

printf '\n'

grub-mkrescue -o HyperOS.iso iso

rm -r iso

printf "\e[92m === Finished Building ISO === \e[39m\n"