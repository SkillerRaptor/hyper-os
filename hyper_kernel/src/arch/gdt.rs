/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use bitflags::bitflags;
use core::{arch::asm, mem};
use log::info;

pub const KERNEL_CODE_SELECTOR: u64 = 0x28;
pub const KERNEL_DATA_SELECTOR: u64 = 0x30;

bitflags! {
    struct AccessAttribute: u8 {
        const NULL = 0;
        const ACCESS = 1 << 0;
        const READ_WRITE = 1 << 1;
        const EXECUTABLE = 1 << 3;
        const CODE_DATA = 1 << 4;
        const PRESENT = 1 << 7;
    }

    struct FlagAttribute: u8 {
        const NULL = 0;
        const GRANULARITY_1B = 0 << 3;
        const GRANULARITY_4K = 1 << 3;
        const SIZE_16 = 0 << 2;
        const SIZE_32 = 1 << 2;
        const SIZE_64 = 1 << 1;
    }
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
struct Entry {
    limit_low: u16,
    base_low: u16,
    base_middle: u8,
    access: u8,
    limit_high_flags: u8,
    base_high: u8,
}

impl Entry {
    fn new(base: u32, limit: u32, access: AccessAttribute, flags: FlagAttribute) -> Self {
        Self {
            limit_low: limit as u16,
            base_low: base as u16,
            base_middle: (base >> 16) as u8,
            access: access.bits(),
            limit_high_flags: (flags.bits() << 4) & 0xf0 | ((limit >> 16) as u8) & 0x0f,
            base_high: (base >> 24) as u8,
        }
    }

    const fn default() -> Self {
        Self {
            limit_low: 0,
            base_low: 0,
            base_middle: 0,
            access: 0,
            limit_high_flags: 0,
            base_high: 0,
        }
    }
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
struct Table {
    null_entry: Entry,
    kernel_entries_16: [Entry; 2],
    kernel_entries_32: [Entry; 2],
    kernel_entries_64: [Entry; 2],
}

impl Table {
    fn new(
        null_entry: Entry,
        kernel_entries_16: [Entry; 2],
        kernel_entries_32: [Entry; 2],
        kernel_entries_64: [Entry; 2],
    ) -> Self {
        Self {
            null_entry,
            kernel_entries_16,
            kernel_entries_32,
            kernel_entries_64,
        }
    }

    const fn default() -> Self {
        Self {
            null_entry: Entry::default(),
            kernel_entries_16: [Entry::default(); 2],
            kernel_entries_32: [Entry::default(); 2],
            kernel_entries_64: [Entry::default(); 2],
        }
    }
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
struct Descriptor {
    size: u16,
    address: u64,
}

impl Descriptor {
    fn new(size: u16, address: u64) -> Self {
        Self { size, address }
    }

    const fn default() -> Self {
        Self {
            size: 0,
            address: 0,
        }
    }
}

static mut TABLE: Table = Table::default();
static mut DESCRIPTOR: Descriptor = Descriptor::default();

pub fn init() {
    let null_entry = Entry::new(
        0x00000000,
        0x00000000,
        AccessAttribute::NULL,
        FlagAttribute::NULL,
    );

    let kernel_entries_16 = [
        Entry::new(
            0x00000000,
            0x0000ffff,
            AccessAttribute::PRESENT
                | AccessAttribute::CODE_DATA
                | AccessAttribute::EXECUTABLE
                | AccessAttribute::READ_WRITE,
            FlagAttribute::NULL,
        ),
        Entry::new(
            0x00000000,
            0x0000ffff,
            AccessAttribute::PRESENT
                | AccessAttribute::CODE_DATA
                | AccessAttribute::READ_WRITE
                | AccessAttribute::ACCESS,
            FlagAttribute::NULL,
        ),
    ];

    let kernel_entries_32 = [
        Entry::new(
            0x00000000,
            0xffffffff,
            AccessAttribute::PRESENT
                | AccessAttribute::CODE_DATA
                | AccessAttribute::EXECUTABLE
                | AccessAttribute::READ_WRITE,
            FlagAttribute::GRANULARITY_4K | FlagAttribute::SIZE_32,
        ),
        Entry::new(
            0x00000000,
            0xffffffff,
            AccessAttribute::PRESENT
                | AccessAttribute::CODE_DATA
                | AccessAttribute::READ_WRITE
                | AccessAttribute::ACCESS,
            FlagAttribute::GRANULARITY_4K | FlagAttribute::SIZE_32,
        ),
    ];

    let kernel_entries_64 = [
        Entry::new(
            0x00000000,
            0xffffffff,
            AccessAttribute::PRESENT
                | AccessAttribute::CODE_DATA
                | AccessAttribute::EXECUTABLE
                | AccessAttribute::READ_WRITE
                | AccessAttribute::ACCESS,
            FlagAttribute::GRANULARITY_4K | FlagAttribute::SIZE_64,
        ),
        Entry::new(
            0x00000000,
            0xffffffff,
            AccessAttribute::PRESENT
                | AccessAttribute::CODE_DATA
                | AccessAttribute::READ_WRITE
                | AccessAttribute::ACCESS,
            FlagAttribute::GRANULARITY_4K | FlagAttribute::SIZE_64,
        ),
    ];

    unsafe {
        TABLE = Table::new(
            null_entry,
            kernel_entries_16,
            kernel_entries_32,
            kernel_entries_64,
        );

        DESCRIPTOR = Descriptor::new(
            (mem::size_of::<Table>() - 1) as u16,
            (&TABLE as *const _) as u64,
        );
    }

    load();

    info!("GDT: Initialized");
}

fn load() {
    unsafe {
        asm!(
            "lgdt [{descriptor}]",
            "push {tmp}",
            "mov {tmp}, rsp",
            "push {data_offset}",
            "push {tmp}",
            "pushf",
            "push {code_offset}",
            "lea {tmp}, [rip + 1f]",
            "push {tmp}",
            "iretq",
            "1:",
            "pop {tmp}",
            "mov ds, {data_offset:x}",
            "mov es, {data_offset:x}",
            "mov fs, {data_offset:x}",
            "mov gs, {data_offset:x}",
            "mov ss, {data_offset:x}",
            descriptor = in(reg) &DESCRIPTOR,
            code_offset = in(reg) KERNEL_CODE_SELECTOR,
            data_offset = in(reg) KERNEL_DATA_SELECTOR,
            tmp = lateout(reg) _,
        );
    }
}
