#!/bin/bash

build_step() {
    NAME=$1
    shift
    "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

build_error() {
    build_step HyperOS echo "Building failed!"
    exit
}

build_step HyperOS echo "Building HyperOS..."

arch=x86_64

if [ "$1" ] 
  then
    if [ $1 != "x86_64" ] && [ $1 != "x86_32" ] 
      then
        build_step HyperOS echo "Unknown architecture $1"
        build_error
      else
        arch="$1"
    fi
fi

if [[ "$OSTYPE" == "darwin"* ]]; then
  realpath() {
      [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
  }

  cores=$(sysctl -n hw.physicalcpu)
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
  cores=$(nproc)
fi

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..
pushd $root_path > /dev/null
build_step Bash mkdir -p Build/$arch || build_error
pushd Build/$arch > /dev/null
build_step CMake cmake --build . --parallel $cores || build_error
popd > /dev/null
popd > /dev/null

build_step HyperOS echo "Building done!"