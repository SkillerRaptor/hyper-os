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

if [[ "$OSTYPE" == "darwin"* ]]; then
  realpath() {
    [[ $1 == /* ]] && echo "$1" || echo "$PWD/${1#./}"
  }

  cores=$(sysctl -n hw.physicalcpu)
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
  cores=$(nproc)
fi

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..
pushd $root_path >/dev/null
build_step Bash mkdir -p Build || build_error
pushd Build >/dev/null
build_step CMake cmake --build . --parallel $cores || build_error
popd >/dev/null
popd >/dev/null

build_step HyperOS echo "Building done!"
