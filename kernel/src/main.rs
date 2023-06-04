/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

#![no_std]
#![no_main]
#![allow(dead_code)]

mod arch;
mod boot;
mod utils;

use crate::{
    arch::{cpu, gdt, interrupts},
    boot::BootInformation,
    utils::logger,
};

use core::panic::PanicInfo;

#[no_mangle]
extern "C" fn kernel_main() -> ! {
    let boot_information = BootInformation::load();

    logger::init(&boot_information);
    gdt::init();

    interrupts::disable();

    loop {
        cpu::halt();
    }
}

#[panic_handler]
fn rust_panic(_panic_info: &PanicInfo) -> ! {
    interrupts::disable();

    loop {
        cpu::halt();
    }
}
