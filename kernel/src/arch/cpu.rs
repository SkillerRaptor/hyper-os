/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

use core::arch::asm;

/// Halts the CPU
///
/// Resumes when next interrupt arrives
#[inline(always)]
pub fn halt() {
    unsafe {
        asm!("hlt", options(nomem, nostack));
    }
}
