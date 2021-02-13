#!/bin/sh

printf "\e[93m === Starting Building === \e[39m\n"

cd ..
find */ -name "Makefile" -execdir make -C . \;
make -C .
cd Scripts

printf "\e[92m === Finished Building === \e[39m\n"