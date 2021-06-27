#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
  realpath() {
    [[ $1 == /* ]] && echo "$1" || echo "$PWD/${1#./}"
  }
fi

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

build_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

build_error() {
  build_step HyperOS echo "Building Cross-Compiler failed!"
  exit
}

pushd $true_path >/dev/null

if [ -e "CrossCompiler/Tools/bin/x86_64-elf-g++" ]; then
  exit 0
else
  build_step HyperOS echo "Building cross-compiler for x86_64..."
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  sudo apt update

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
elif [[ "$OSTYPE" == "darwin"* ]]; then
  declare -a dependencies=(
    "bison"
    "flex"
    "gmp"
    "libmpc"
    "mpfr"
    "texinfo"
    "isl"
    "libmpc"
    "wget"
  )
fi

for dependency in "${dependencies[@]}"; do
  build_step Dependencies echo -n $dependency
  if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    is_dependency_installed=$(dpkg-query -l | grep $dependency)
  elif [[ "$OSTYPE" == "darwin"* ]]; then
    is_dependency_installed=$(brew list $dependency)
  fi

  if [ -z "$is_dependency_installed" ]; then
    build_step Dependencies echo " - not installed"
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
      build_step Dependencies sudo apt install -y $dependency || build_error
    elif [[ "$OSTYPE" == "darwin"* ]]; then
      build_step Dependencies brew install $dependency || build_error
    fi
  else
    echo " - installed"
  fi
done

binutils_version="binutils-2.34"
binutils_url="https://ftp.gnu.org/gnu/binutils/$binutils_version.tar.gz"
gcc_version="gcc-10.1.0"
gcc_url="ftp://ftp.gnu.org/gnu/gcc/$gcc_version/$gcc_version.tar.gz"

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

if [ ! -e "CrossCompiler/gcc/configure" ]; then
  build_step GCC echo "Downloading GCC source files..."
  build_step GCC mkdir -p "CrossCompiler" || build_error
  build_step GCC mkdir -p "CrossCompiler/gcc" || build_error
  build_step GCC wget -O "CrossCompiler/gcc.tar.gz" $gcc_url || build_error
  build_step GCC echo "Unpacking GCC source files..."
  build_step GCC tar -xf "CrossCompiler/gcc.tar.gz" -C "CrossCompiler/gcc" --strip-components 1 || build_error
  build_step GCC rm "CrossCompiler/gcc.tar.gz"
else
  build_step GCC echo "GCC is already downloaded!"
fi

export PREFIX="$true_path/CrossCompiler/Tools"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

export CFLAGS="-g0 -O2"
export CXXFLAGS="-g0 -O2"

build_step binutils echo "Building binutils..."
build_step binutils mkdir -p "CrossCompiler/binutils_build" || build_error

pushd "CrossCompiler/binutils_build" >/dev/null
build_step binutils ../../binutils/configure --target=$TARGET \
  --prefix="$PREFIX" \
  --with-sysroot \
  --disable-nls \
  --disable-werror || build_error
build_step binutils make || build_error
build_step binutils make install || build_error
popd >/dev/null

build_step GCC echo "Building GCC..."
build_step GCC mkdir -p "CrossCompiler/gcc_build" || build_error
pushd "CrossCompiler/gcc_build" >/dev/null

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  build_step GCC ../../gcc/configure --target=$TARGET \
    --prefix="$PREFIX" \
    --disable-nls \
    --enable-languages=c,c++ \
    --without-headers || build_error
elif [[ "$OSTYPE" == "darwin"* ]]; then
  build_step GCC ../../gcc/configure --target=$TARGET \
    --prefix="$PREFIX" \
    --disable-nls \
    --enable-languages=c,c++ \
    --without-headers \
    --with-gmp=/usr/local/opt/gmp \
    --with-mpc=/usr/local/opt/libmpc \
    --with-mpfr=/usr/local/opt/mpfr || build_error
fi

build_step GCC make all-gcc || build_error
build_step GCC make all-target-libgcc || build_error
build_step GCC make install-gcc || build_error
build_step GCC make install-target-libgcc || build_error

popd >/dev/null
popd >/dev/null

build_step HyperOS echo "Building done!"
