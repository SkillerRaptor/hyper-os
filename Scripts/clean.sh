#!/bin/sh

printf "\e[93m === Starting Cleaning === \e[39m\n"

make -C ../Libraries/LibC clean
make -C ../Kernel clean

printf "\e[92m === Finished Cleaning === \e[39m\n"