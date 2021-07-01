#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

arch="x86_64"

install_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

install_error() {
  install_step HyperOS echo "Installing failed!"
  exit
}

install_step HyperOS echo "Installing HyperOS..."

pushd "$root_path" >/dev/null || install_error
install_step Bash mkdir -p Build/$arch || install_error
pushd Build/$arch >/dev/null || install_error
install_step CMake cmake --install . || install_error
popd >/dev/null || install_error
popd >/dev/null || install_error

install_step HyperOS echo "Installing done!"
