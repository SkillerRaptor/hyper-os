/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#![no_std]
#![no_main]
mod arch;
mod common;

use crate::{arch::gdt, common::logger};

use core::panic::PanicInfo;
use limine::*;
use log::info;

static BOOTLOADER_INFO: LimineBootInfoRequest = LimineBootInfoRequest::new(0);

#[panic_handler]
fn panic(_: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
extern "C" fn kernel_main() -> ! {
    logger::init();

    let bootloader_info = BOOTLOADER_INFO.get_response().get().unwrap();
    let bootloader_name = {
        let c_string = bootloader_info.name.to_str().unwrap();
        c_string.to_str().unwrap()
    };
    let bootloader_version = {
        let c_string = bootloader_info.version.to_str().unwrap();
        c_string.to_str().unwrap()
    };

    info!("");
    info!("_  _ _   _ ___  ____ ____ ____ ____ ");
    info!("|__|  \\_/  |__] |___ |__/ |  | [__  ");
    info!("|  |   |   |    |___ |  \\ |__| ___] ");
    info!("");
    info!("Booted with {} v{}", bootloader_name, bootloader_version);
    info!("");

    gdt::init();

    loop {}
}
