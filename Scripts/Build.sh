#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

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

pushd "$root_path" >/dev/null || build_error
build_step Bash mkdir -p Build || build_error
pushd Build >/dev/null || build_error
build_step CMake cmake --build . --parallel "$(nproc)" || build_error
popd >/dev/null || build_error
popd >/dev/null || build_error

build_step HyperOS echo "Building done!"
