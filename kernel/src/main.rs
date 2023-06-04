/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

#![no_std]
#![no_main]
#![allow(dead_code)]

mod arch;

use crate::arch::gdt;

use core::{arch::asm, panic::PanicInfo};

#[no_mangle]
extern "C" fn kernel_main() -> ! {
    gdt::init();

    unsafe {
        asm!("cli");

        loop {
            asm!("hlt");
        }
    }
}

#[panic_handler]
fn rust_panic(_panic_info: &PanicInfo) -> ! {
    unsafe {
        asm!("cli");

        loop {
            asm!("hlt");
        }
    }
}
