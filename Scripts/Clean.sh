#!/bin/sh

printf "\e[93m === Starting Cleaning === \e[39m\n"

make -C ./Userland/Libraries/LibGUI clean
make -C ./Userland/Libraries/LibC clean
make -C ./Kernel clean
make -C ./AK clean

rm -f HyperOS.elf
rm -r ./build

printf "\e[92m === Finished Cleaning === \e[39m\n"