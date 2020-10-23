#!/bin/sh

sh ./build.sh

printf "\n\e[93m === Starting Building ISO === \e[39m\n"

cd ..
mkdir -p iso/boot/grub
cd iso/boot/grub
curl -L -O https://github.com/whitequark/story-os/raw/master/grub/stage2_eltorito --output ./stage2_eltorito
printf 'default 0\ntimeout 0\n\ntitle HyperOS\nkernel /boot/HyperOS.bin' > menu.lst
printf 'menuentry "HyperOS" {\n    multiboot /boot/HyperOS.bin\n}' > grub.cfg
cd ../../..
cp HyperOS.bin iso/boot

printf '\n'

genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o HyperOS.iso iso

rm -r iso

printf "\e[92m === Finished Building ISO === \e[39m\n"