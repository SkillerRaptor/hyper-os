/*
 * Copyright (c) 2022, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

use crate::{
    arch::gdt,
    arch::{cpu, pic, registers::Registers},
};

use bitflags::bitflags;
use core::{arch::asm, mem};
use log::{error, info};

bitflags! {
    struct Attributes: u8 {
        const INTERRUPT_GATE = 1<<1 | 1<< 2 | 1 << 3;
        const PRESENT = 1 << 7;
    }
}

#[repr(C, packed)]
#[derive(Debug, Clone, Copy)]
struct Entry {
    offset_low: u16,
    selector: u16,
    ist: u8,
    attribute: u8,
    offset_middle: u16,
    offset_high: u32,
    zero: u32,
}

impl Entry {
    fn new(index: usize, handler: *const u8, attribute: Attributes) -> Self {
        let handler_address = handler as usize;
        Self {
            offset_low: handler_address as u16,
            selector: gdt::KERNEL_CODE_SELECTOR as u16,
            ist: 0,
            attribute: attribute.bits(),
            offset_middle: (handler_address >> 16) as u16,
            offset_high: (handler_address >> 32) as u32,
            zero: 0,
        }
    }

    const fn default() -> Self {
        Self {
            offset_low: 0,
            selector: 0,
            ist: 0,
            attribute: 0,
            offset_middle: 0,
            offset_high: 0,
            zero: 0,
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

static mut TABLE: [Entry; 256] = [Entry::default(); 256];
static mut DESCRIPTOR: Descriptor = Descriptor::default();
static mut HANDLERS: [Option<fn(&mut Registers)>; 256] = [None; 256];

pub fn init() {
    extern "C" {
        static interrupt_handlers: [*const u8; 256];
    }

    unsafe {
        // Exception Handlers
        HANDLERS[0] = Some(divide_by_zero);
        HANDLERS[1] = Some(debug);
        HANDLERS[2] = Some(non_maskable_interrupt);
        HANDLERS[3] = Some(breakpoint);
        HANDLERS[4] = Some(overflow);
        HANDLERS[5] = Some(bound_range_exceeded);
        HANDLERS[6] = Some(invalid_opcode);
        HANDLERS[7] = Some(device_not_available);
        HANDLERS[8] = Some(double_fault);

        HANDLERS[10] = Some(invalid_tss);
        HANDLERS[11] = Some(segment_not_present);
        HANDLERS[12] = Some(stack_segment_fault);
        HANDLERS[13] = Some(general_protection_fault);
        HANDLERS[14] = Some(page_fault);

        HANDLERS[16] = Some(x87_floating_point_exception);
        HANDLERS[17] = Some(alignment_check);
        HANDLERS[18] = Some(machine_check);
        HANDLERS[19] = Some(simd_floating_point_exception);
        HANDLERS[20] = Some(virtualization_exception);

        HANDLERS[30] = Some(security_exception);

        // Interrupt Handlers (starting at 0x20)

        for (i, entry) in &mut TABLE.iter_mut().enumerate() {
            *entry = Entry::new(
                i,
                interrupt_handlers[i],
                Attributes::PRESENT | Attributes::INTERRUPT_GATE,
            );
        }

        DESCRIPTOR = Descriptor::new(
            (mem::size_of::<[Entry; 256]>() - 1) as u16,
            (&TABLE as *const _) as u64,
        );
    }

    load();

    info!("Initialized IDT");
}

fn load() {
    unsafe {
        asm!(
            "lidt [{descriptor}]",
            descriptor = in(reg) &DESCRIPTOR,
        );
    }

    cpu::enable_interrupts();
}

#[no_mangle]
extern "C" fn idt_raise(isr: usize, registers: *mut Registers) {
    let mut registers = unsafe { &mut *registers };

    if let Some(handler) = unsafe { HANDLERS[isr] } {
        handler(&mut registers);
    }

    pic::end_of_interrupt(isr as u8);
}

#[macro_export]
macro_rules! exception_handler {
    ($name:ident => $message:expr) => {
        fn $name(_: &mut Registers) {
            error!("Exception: {}", $message);

            loop {
                cpu::halt();
            }
        }
    };
}

exception_handler!(divide_by_zero => "Divide-by-zero Error");
exception_handler!(debug => "Debug");
exception_handler!(non_maskable_interrupt => "Non-maskable Interrupt");
exception_handler!(breakpoint => "Breakpoint");
exception_handler!(overflow => "Overflow");
exception_handler!(bound_range_exceeded => "Bound Range Exceeded");
exception_handler!(invalid_opcode => "Invalid Opcode");
exception_handler!(device_not_available => "Device Not Available");
exception_handler!(double_fault => "Double Fault");

exception_handler!(invalid_tss => "Invalid TSS");
exception_handler!(segment_not_present => "Segment Not Present");
exception_handler!(stack_segment_fault => "Stack-Segment-Fault");
exception_handler!(general_protection_fault => "General-Protection-Fault");
exception_handler!(page_fault => "Page Fault");

exception_handler!(x87_floating_point_exception => "x87 Floating-Point Exception");
exception_handler!(alignment_check => "Alignment Check");
exception_handler!(machine_check => "Machine Check");
exception_handler!(simd_floating_point_exception => "SIMD Floating-Point Exception	");
exception_handler!(virtualization_exception => "Virtualization Exception");

exception_handler!(security_exception => "Security Exception");
