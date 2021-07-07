#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

clean_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

clean_error() {
  clean_step HyperOS echo "Cleaning failed!"
  exit
}

clean_step HyperOS echo "Cleaning HyperOS..."

pushd "$root_path" >/dev/null || clean_error
clean_step Bash mkdir -p Build || clean_error
pushd Build >/dev/null || clean_error
clean_step CMake cmake --build . --target clean || clean_error
clean_step Bash rm -rf Root || clean_error
popd >/dev/null || clean_error
popd >/dev/null || clean_error

clean_step HyperOS echo "Cleaning done!"
