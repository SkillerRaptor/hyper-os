/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use log::info;

use crate::arch::io;

const MASTER_COMMAND_SELECTOR: u16 = 0x20;
const MASTER_DATA_SELECTOR: u16 = 0x21;
const MASTER_OFFSET: u8 = 0x20;

const SLAVE_COMMAND_SELECTOR: u16 = 0xA0;
const SLAVE_DATA_SELECTOR: u16 = 0xA1;
const SLAVE_OFFSET: u8 = 0x28;

const ICW1_ICW4: u8 = 1 << 0;
const ICW1_INIT: u8 = 1 << 4;
const ICW1_8086: u8 = 1 << 0;

const MASTER_IDENTITY: u8 = 0x04;
const SLAVE_IDENTITY: u8 = 0x02;

const END_INTERRUPT_CODE: u8 = 0x20;

pub fn remap() {
    io::out8(MASTER_COMMAND_SELECTOR, ICW1_INIT | ICW1_ICW4);
    io::out8(SLAVE_COMMAND_SELECTOR, ICW1_INIT | ICW1_ICW4);

    io::out8(MASTER_DATA_SELECTOR, MASTER_OFFSET);
    io::out8(SLAVE_DATA_SELECTOR, SLAVE_OFFSET);

    io::out8(MASTER_DATA_SELECTOR, MASTER_IDENTITY);
    io::out8(SLAVE_DATA_SELECTOR, SLAVE_IDENTITY);

    io::out8(MASTER_DATA_SELECTOR, ICW1_8086);
    io::out8(SLAVE_DATA_SELECTOR, ICW1_8086);
}

pub fn end_of_interrupt(isr: u8) {
    if isr >= 0x8 {
        io::out8(SLAVE_COMMAND_SELECTOR, END_INTERRUPT_CODE);
    }

    io::out8(MASTER_COMMAND_SELECTOR, END_INTERRUPT_CODE);
}
