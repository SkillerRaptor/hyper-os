#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

arch="x86_64"

build_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

build_error() {
  build_step HyperOS echo "Building failed!"
  exit
}

build_step HyperOS echo "Building image..."

pushd "$root_path" >/dev/null || build_error
build_step Bash mkdir -p Build/$arch || build_error
pushd Build/$arch >/dev/null || build_error
build_step CMake cmake --build . --target image || build_error
popd >/dev/null || build_error
popd >/dev/null || build_error

build_step HyperOS echo "Building image done!"
