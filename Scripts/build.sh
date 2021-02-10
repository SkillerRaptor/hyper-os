#!/bin/sh

printf "\e[93m === Starting Building === \e[39m\n"

make -C ../Userland/Libraries/LibGUI
make -C ../Userland/Libraries/LibC
make -C ../Kernel
make -C ../AK
make -C ..

printf "\e[92m === Finished Building === \e[39m\n"