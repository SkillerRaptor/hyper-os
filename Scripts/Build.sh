#!/bin/sh

printf "\e[93m === Starting Building === \e[39m\n"

find */ -name "ThirdParty" -prune -o -name "Makefile" -execdir make -C . \;
make -C .

printf "\e[92m === Finished Building === \e[39m\n"

printf "\n\e[93m === Starting Building HDD === \e[39m\n"

mkdir ./build
rm -f ./build/HyperOS.hdd

dd if=/dev/zero bs=1M count=0 seek=64 of=./build/HyperOS.hdd

parted -s ./build/HyperOS.hdd mklabel msdos
parted -s ./build/HyperOS.hdd mkpart primary 1 100%
parted -s ./build/HyperOS.hdd set 1 boot on

./ThirdParty/echfs/echfs-utils -m -p0 ./build/HyperOS.hdd quick-format 32768
./ThirdParty/echfs/echfs-utils -m -p0 ./build/HyperOS.hdd import ./HyperOS.elf HyperOS.elf
./ThirdParty/echfs/echfs-utils -m -p0 ./build/HyperOS.hdd import ./limine.cfg limine.cfg

./ThirdParty/limine/limine-install ./limine.bin ./build/HyperOS.hdd

printf "\e[92m === Finished Building HDD === \e[39m\n"