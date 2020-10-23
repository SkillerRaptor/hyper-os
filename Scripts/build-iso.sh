#!/bin/sh

sh ./build.sh

printf "\n\e[93m === Starting Building ISO === \e[39m\n"

cp ../HyperOS.bin ../Iso/boot
cd ..
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -input-charset utf-8 -o HyperOS.iso iso

printf "\e[92m === Finished Building ISO === \e[39m\n"