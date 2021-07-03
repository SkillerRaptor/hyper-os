#!/bin/bash

current_path="$(dirname "$(realpath "$0")")"

build_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

build_error() {
  build_step HyperOS echo "Building cross-compiler for x86_64 failed!"
  exit
}

pushd "$current_path" >/dev/null || build_error

if [ -e "CrossCompiler/Tools/bin/x86_64-elf-g++" ]; then
  exit 0
else
  build_step HyperOS echo "Building cross-compiler for x86_64..."
fi

build_step Dependencies sudo apt update
build_step Dependencies sudo apt upgrade

declare -a dependencies=(
  "bison"
  "flex"
  "libgmp-dev"
  "libmpc-dev"
  "libmpfr-dev"
  "texinfo"
  "libisl-dev"
  "build-essential"
)

for dependency in "${dependencies[@]}"; do
  build_step Dependencies echo -n "$dependency"
  is_dependency_installed=$(dpkg-query -l | grep "$dependency")

  if [ -z "$is_dependency_installed" ]; then
    echo " - not installed"
    build_step Dependencies sudo apt install -y "$dependency" || build_error
  else
    echo " - installed"
  fi
done

binutils_version="binutils-2.36"
binutils_url="https://ftp.gnu.org/gnu/binutils/$binutils_version.tar.gz"
if [ ! -e "CrossCompiler/binutils/configure" ]; then
  build_step binutils echo "Downloading binutils source files..."
  build_step binutils mkdir -p "CrossCompiler" || build_error
  build_step binutils mkdir -p "CrossCompiler/binutils" || build_error
  build_step binutils wget -O "CrossCompiler/binutils.tar.gz" $binutils_url || build_error
  build_step binutils echo "Unpacking binutils source files..."
  build_step binutils tar -xf "CrossCompiler/binutils.tar.gz" -C "CrossCompiler/binutils" --strip-components 1 || build_error
  build_step binutils rm "CrossCompiler/binutils.tar.gz"
else
  build_step binutils echo "binutils is already downloaded!"
fi

gcc_version="gcc-11.1.0"
gcc_url="https://ftp.gnu.org/gnu/gcc/$gcc_version/$gcc_version.tar.gz"
if [ ! -e "CrossCompiler/gcc/configure" ]; then
  build_step gcc echo "Downloading gcc source files..."
  build_step gcc mkdir -p "CrossCompiler" || build_error
  build_step gcc mkdir -p "CrossCompiler/gcc" || build_error
  build_step gcc wget -O "CrossCompiler/gcc.tar.gz" $gcc_url || build_error
  build_step gcc echo "Unpacking gcc source files..."
  build_step gcc tar -xf "CrossCompiler/gcc.tar.gz" -C "CrossCompiler/gcc" --strip-components 1 || build_error
  build_step gcc rm "CrossCompiler/gcc.tar.gz"
else
  build_step gcc echo "gcc is already downloaded!"
fi

export PREFIX="$current_path/CrossCompiler/Tools"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

export CFLAGS="-g0 -O3"
export CXXFLAGS="-g0 -O3"

build_step binutils echo "Building binutils..."
build_step binutils mkdir -p "CrossCompiler/binutils_build" || build_error
pushd "CrossCompiler/binutils_build/$arch" >/dev/null || build_error
build_step binutils ../../binutils/configure --target=$TARGET \
  --prefix="$PREFIX" \
  --with-sysroot \
  --disable-nls \
  --disable-werror || build_error
build_step binutils make || build_error
build_step binutils make install || build_error
build_step binutils echo "Building binutils finished!"
popd >/dev/null || build_error

build_step gcc echo "Building gcc..."
build_step gcc mkdir -p "CrossCompiler/gcc_build" || build_error
pushd "CrossCompiler/gcc_build/$arch" >/dev/null || build_error
build_step gcc ../../gcc/configure --target=$TARGET \
  --prefix="$PREFIX" \
  --disable-nls \
  --enable-languages=c,c++ \
  --without-headers || build_error
build_step gcc make all-gcc || build_error
build_step gcc make all-target-libgcc || build_error
build_step gcc make install-gcc || build_error
build_step gcc make install-target-libgcc || build_error
build_step gcc echo "Building gcc finished!"

popd >/dev/null || build_error
popd >/dev/null || build_error

build_step HyperOS echo "Building cross-compiler for x86_64 done!"
