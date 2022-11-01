/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use core::arch::asm;

pub fn in8(port: u16) -> u8 {
    let mut ret: u8 = 0;

    unsafe {
        asm!(
            "in al, dx",
            in("dx") port,
            out("al") ret,
            options(preserves_flags, nomem, nostack)
        );
    }

    ret
}

pub fn out8(port: u16, value: u8) {
    unsafe {
        asm!(
           "out dx, al",
           in("dx") port,
           in("al") value,
           options(preserves_flags, nomem, nostack)
        );
    }
}

pub fn in16(port: u16) -> u16 {
    let mut ret: u16 = 0;

    unsafe {
        asm!(
            "in ax, dx",
            in("dx") port,
            out("ax") ret,
            options(preserves_flags, nomem, nostack)
        );
    }

    ret
}

pub fn out16(port: u16, value: u16) {
    unsafe {
        asm!(
           "out dx, ax",
           in("dx") port,
           in("ax") value,
           options(preserves_flags, nomem, nostack)
        );
    }
}

pub fn in32(port: u16) -> u32 {
    let mut ret: u32 = 0;

    unsafe {
        asm!(
            "in eax, dx",
            in("dx") port,
            out("eax") ret,
            options(preserves_flags, nomem, nostack)
        );
    }

    ret
}

pub fn out32(port: u16, value: u32) {
    unsafe {
        asm!(
           "out dx, eax",
           in("dx") port,
           in("eax") value,
           options(preserves_flags, nomem, nostack)
        );
    }
}

pub fn wait() {
    out8(0x80, 0x00);
}
