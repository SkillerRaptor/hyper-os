#!/bin/sh

sh ./clean.sh

printf "\e[93m === Starting Building === \e[39m\n"

make -C ../Libraries/LibC
make -C ../Kernel
make -C ../AK
make -C ..

printf "\e[92m === Finished Building === \e[39m\n"