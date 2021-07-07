;
; Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
;
; SPDX-License-Identifier: MIT
;

%include "Kernel/Common/Common.asm"

bits 64
section .text

global switch_task
switch_task:
    cli
    mov rsp, rdi
    popaq
    add rsp, 0x10
    iretq
