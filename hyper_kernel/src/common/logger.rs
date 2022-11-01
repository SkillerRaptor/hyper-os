/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use crate::{print, println};

use log::{Level, LevelFilter, Log};

static LOGGER: HyperLogger = HyperLogger;

struct HyperLogger;

impl Log for HyperLogger {
    fn enabled(&self, _: &log::Metadata) -> bool {
        true
    }

    fn log(&self, record: &log::Record) {
        if !self.enabled(record.metadata()) {
            return;
        }

        // TODO: Add locks for scheduler
        match record.level() {
            Level::Info => print!("\x1b[32;1minfo"),
            Level::Warn => print!("\x1b[93;1mwarn"),
            Level::Error => print!("\x1b[31;1merror"),
            Level::Debug => print!("\x1b[36;1mdebug"),
            Level::Trace => print!("\x1b[35;1mtrace"),
        }

        if record.target() == "hyper_kernel" {
            println!("\x1b[0m: {}", record.args());
        } else {
            println!("\x1b[0m: {}: {}", record.target(), record.args());
        }
    }

    fn flush(&self) {}
}

pub fn init() {
    let log_level = if cfg!(debug_assertions) {
        LevelFilter::Trace
    } else {
        LevelFilter::Info
    };

    log::set_logger(&LOGGER)
        .map(|()| log::set_max_level(log_level))
        .unwrap();
}
