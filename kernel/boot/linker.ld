/*
 * Copyright (c) 2023, SkillerRaptor
 *
 * SPDX-License-Identifier: MIT
 */

OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(kernel_main)

PHDRS
{
    text    PT_LOAD    FLAGS((1 << 0) | (1 << 2)) ;
    rodata  PT_LOAD    FLAGS((1 << 2)) ;
    data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ;
    dynamic PT_DYNAMIC FLAGS((1 << 1) | (1 << 2)) ;
}

SECTIONS
{
    . = 0xffffffff80000000;

    .text : {
        *(.text .text.*)
    } :text

    . += CONSTANT(MAXPAGESIZE);

    .dynsym : {
        *(.dynsym)
    } :rodata

    .dynstr : {
        *(.dynstr)
    } :rodata

    .rela : {
        *(.rela*)
    } :rodata

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    . += CONSTANT(MAXPAGESIZE);

    .dynamic : {
        *(.dynamic)
    } :data :dynamic

    .got : {
        *(.got)
    } :data

    .data : {
        *(.data.rel.ro .data.rel.ro.*)
        *(.data .data.*)
    } :data

    .bss : {
        *(COMMON)
        *(.dynbss)
        *(.bss .bss.*)
    } :data

    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
    }
}
