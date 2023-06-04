/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

use crate::boot::BootInformation;

use core::fmt::{self, Arguments, Write};
use limine::LimineTerminalResponse;
use spin::Mutex;

static WRITER: Mutex<Writer> = Mutex::new(Writer { terminals: None });

pub struct Writer {
    terminals: Option<&'static LimineTerminalResponse>,
}

unsafe impl Send for Writer {}

impl Write for Writer {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        let terminals = self.terminals.unwrap();

        let write = terminals.write().unwrap();
        for terminal in terminals.terminals() {
            write(terminal, s);
        }

        Ok(())
    }
}

pub fn _print(args: Arguments) {
    let mut writer = WRITER.lock();
    writer.write_fmt(args).ok();
}

pub fn init(boot_information: &BootInformation) {
    WRITER.lock().terminals = Some(boot_information.terminal);
}

#[macro_export]
macro_rules! print {
    ($($t:tt)*) => {
        $crate::utils::writer::_print(format_args!($($t)*))
    };
}

#[macro_export]
macro_rules! println {
    () => {
        $crate::utils::writer::_print(format_args!("\n"))
    };
    ($($t:tt)*) => {
        $crate::utils::writer::_print(format_args!("{}\n", format_args!($($t)*)))
    };
}
