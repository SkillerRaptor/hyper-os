/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use core::fmt::{self, Arguments, Write};
use limine::{LimineTerminalRequest, LimineTerminalResponse};

static TERMINAL_REQUEST: LimineTerminalRequest = LimineTerminalRequest::new(0);

struct Writer;

impl Write for Writer {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        static mut CACHED_RESPONSE: Option<&'static LimineTerminalResponse> = None;

        if unsafe { CACHED_RESPONSE.is_none() } {
            let response = TERMINAL_REQUEST.get_response().get().unwrap();
            unsafe {
                CACHED_RESPONSE = Some(response);
            }
        }

        let writer = unsafe { CACHED_RESPONSE.unwrap() };
        let terminal = &writer.terminals()[0];
        writer.write().unwrap()(&terminal, s);

        Ok(())
    }
}

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => ($crate::common::writer::_print(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! println {
    () => (print!("\n"));
    ($($arg:tt)*) => (print!("{}\n", format_args!($($arg)*)));
}

#[doc(hidden)]
pub fn _print(args: Arguments) {
    let mut writer = Writer;
    writer.write_fmt(args).unwrap();
}
