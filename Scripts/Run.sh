#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

arch="x86_64"

run_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

run_error() {
  run_step HyperOS echo "Running failed!"
  exit
}

run_step HyperOS echo "Running HyperOS..."

pushd "$root_path" >/dev/null || run_error
run_step Bash mkdir -p Build/$arch || run_error
pushd Build/$arch >/dev/null || run_error
run_step CMake cmake --build . --target run || run_error
popd >/dev/null || run_error
popd >/dev/null || run_error

run_step HyperOS echo "Running done!"
