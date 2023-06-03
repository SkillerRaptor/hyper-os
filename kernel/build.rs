/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

fn main() {
    println!("cargo:rustc-link-arg=-T./kernel/boot/linker.ld");
    println!("cargo:rerun-if-changed=./kernel/boot/linker.ld");
}
