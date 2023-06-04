/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

use crate::{boot::BootInformation, print, println, utils::writer};

use log::{Level, LevelFilter, Log, Metadata, Record};

static LOGGER: Logger = Logger;

struct Logger;

impl Log for Logger {
    fn enabled(&self, metadata: &Metadata) -> bool {
        metadata.level() <= Level::Trace
    }

    fn log(&self, record: &Record) {
        if !self.enabled(record.metadata()) {
            return;
        }

        match record.level() {
            Level::Info => print!("\x1b[32;1m INFO  "),
            Level::Warn => print!("\x1b[33;1m WARN  "),
            Level::Error => print!("\x1b[31;1m ERROR "),
            Level::Debug => print!("\x1b[36;1m DEBUG "),
            Level::Trace => print!("\x1b[35;1m TRACE "),
        }

        println!("\x1b[0m{}", record.args());
    }

    fn flush(&self) {}
}

pub fn init(boot_information: &BootInformation) {
    writer::init(boot_information);
    log::set_logger(&LOGGER)
        .map(|()| log::set_max_level(LevelFilter::Trace))
        .unwrap();
}
