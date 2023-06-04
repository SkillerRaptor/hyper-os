/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

use core::arch::asm;

/// Enables interrupts
///
/// Sets the interrupt flag
#[inline(always)]
pub fn enable_interrupts() {
    unsafe {
        asm!("sti", options(nomem, nostack));
    }
}

/// Disables interrupts
///
/// Clears the interrupt flag
#[inline(always)]
pub fn disable_interrupts() {
    unsafe {
        asm!("cli", options(nomem, nostack));
    }
}

/// Halts the CPU
#[inline(always)]
pub fn halt() {
    unsafe {
        asm!("hlt", options(nomem, nostack));
    }
}
