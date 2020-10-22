#!/bin/sh

make -C ../Libraries/LibC clean
make -C ../Libraries/LibC
make -C ../Kernel clean
make -C ../Kernel