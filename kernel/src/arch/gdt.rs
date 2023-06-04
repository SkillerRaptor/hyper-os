/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
*/

use crate::arch::cpu;

use core::{arch::asm, mem};

pub const KERNEL_CODE_SELECTOR: u64 = 0x28;
pub const KERNEL_DATA_SELECTOR: u64 = 0x30;

bitflags::bitflags! {
    #[derive(Clone, Copy, Debug)]
    struct AccessAttribute: u8 {
        const NULL = 0;
        const ACCESS = 1 << 0;
        const READ_WRITE = 1 << 1;
        const DIRECTION = 1 << 2;
        const EXECUTABLE = 1 << 3;
        const CODE_DATA = 1 << 4;
        const PRIVILEGE_KERNEL = 0 << 5 | 0 << 6;
        const PRIVILEGE_USER = 1 << 5 | 1 << 6;
        const PRESENT = 1 << 7;
    }

    #[derive(Clone, Copy, Debug)]
    struct FlagAttribute: u8 {
        const NULL = 0;
        const SIZE_64 = 1 << 1;
        const SIZE_16 = 0 << 2;
        const SIZE_32 = 1 << 2;
        const GRANULARITY_1B = 0 << 3;
        const GRANULARITY_4K = 1 << 3;
    }
}

#[repr(C, packed)]
#[derive(Clone, Copy, Debug)]
struct Descriptor {
    size: u16,
    offset: u64,
}

impl Descriptor {
    fn new(size: u16, offset: u64) -> Self {
        Self { size, offset }
    }

    const fn null() -> Self {
        Self { size: 0, offset: 0 }
    }
}

#[repr(C, packed)]
#[derive(Clone, Copy, Debug)]
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
        let limit_high = ((limit >> 16) & 0x0f) as u8;
        let flags = (flags.bits() << 4) & 0xf0;
        Self {
            limit_low: ((limit >> 0) & 0xffff) as u16,
            base_low: ((base >> 0) & 0xffff) as u16,
            base_middle: ((base >> 16) & 0xff) as u8,
            access: access.bits(),
            limit_high_flags: flags | limit_high,
            base_high: ((base >> 24) & 0xff) as u8,
        }
    }

    const fn null() -> Self {
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
#[derive(Clone, Copy, Debug)]
struct Gdt {
    null_entry: Entry,
    kernel_entries_16: [Entry; 2],
    kernel_entries_32: [Entry; 2],
    kernel_entries_64: [Entry; 2],
}

impl Gdt {
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

    const fn null() -> Self {
        Self {
            null_entry: Entry::null(),
            kernel_entries_16: [Entry::null(); 2],
            kernel_entries_32: [Entry::null(); 2],
            kernel_entries_64: [Entry::null(); 2],
        }
    }
}

static mut GDT: Gdt = Gdt::null();
static mut DESCRIPTOR: Descriptor = Descriptor::null();

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
        GDT = Gdt::new(
            null_entry,
            kernel_entries_16,
            kernel_entries_32,
            kernel_entries_64,
        );

        DESCRIPTOR = Descriptor::new(
            (mem::size_of::<Gdt>() - 1) as u16,
            (&GDT as *const _) as u64,
        );
    }

    install();
}

fn install() {
    cpu::disable_interrupts();

    unsafe {
        asm!(
            "lgdt [{descriptor}]",
            "push {code_selector}",
            "lea {tmp}, [rip + 1f]",
            "push {tmp}",
            "retfq",
            "1:",
            "mov ds, {data_selector:x}",
            "mov es, {data_selector:x}",
            "mov fs, {data_selector:x}",
            "mov gs, {data_selector:x}",
            "mov ss, {data_selector:x}",
            descriptor = in(reg) &DESCRIPTOR,
            code_selector = in(reg) KERNEL_CODE_SELECTOR,
            data_selector = in(reg) KERNEL_DATA_SELECTOR,
            tmp = lateout(reg) _,
        );
    }
}
