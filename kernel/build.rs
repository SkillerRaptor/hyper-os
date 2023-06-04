/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

fn main() {
    println!("cargo:rustc-link-arg=-T./boot/linker.ld");
    println!("cargo:rerun-if-changed=./boot/linker.ld");
}
