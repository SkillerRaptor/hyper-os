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
pub fn enable() {
    unsafe {
        asm!("sti", options(nomem, nostack));
    }
}

/// Disables interrupts
///
/// Clears the interrupt flag
#[inline(always)]
pub fn disable() {
    unsafe {
        asm!("cli", options(nomem, nostack));
    }
}
