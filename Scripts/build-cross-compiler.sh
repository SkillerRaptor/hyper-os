#!/bin/sh

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $HOME/opt/cross
mkdir -p $HOME/src

sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev

# Setting Binutils up
cd $HOME/src

sudo wget -c https://ftp.gnu.org/gnu/binutils/binutils-2.35.tar.gz -O - | sudo tar -xz
 
mkdir build-binutils
cd build-binutils
../binutils-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

# Setting GCC up
cd $HOME/src
 
which -- $TARGET-as || echo $TARGET-as is not in the PATH

sudo wget -c https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz -O - | sudo tar -xz
 
mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

export PATH="$HOME/opt/cross/bin:$PATH"