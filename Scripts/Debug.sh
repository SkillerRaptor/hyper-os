#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

debug_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

debug_error() {
  debug_step HyperOS echo "Debugging failed!"
  exit
}

debug_step HyperOS echo "Debugging HyperOS..."

pushd "$root_path" >/dev/null || debug_error
debug_step Bash mkdir -p Build || debug_error
pushd Build >/dev/null || debug_error
debug_step CMake cmake --build . --target debug || debug_error
popd >/dev/null || debug_error
popd >/dev/null || debug_error

debug_step HyperOS echo "Debugging done!"
