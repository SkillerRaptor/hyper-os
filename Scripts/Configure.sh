#!/bin/bash

true_path="$(dirname "$(realpath "$0")")"
root_path=$true_path/..

arch="x86_64"

configure_step() {
  NAME=$1
  shift
  "$@" 2>&1 | sed $'s|^|\x1b[34m['"${NAME}"']\x1b[39m |'
}

configure_error() {
  configure_step HyperOS echo "Configuring failed!"
  exit
}

configure_step HyperOS echo "Configuring HyperOS..."

pushd "$root_path" >/dev/null || configure_error
configure_step Bash mkdir -p Build/$arch || configure_error
pushd Build/$arch >/dev/null || configure_error
configure_step CMake cmake ./../.. -G "Ninja" -DARCH=$arch || build_error
popd >/dev/null || configure_error
popd >/dev/null || configure_error

configure_step HyperOS echo "Configuring done!"
