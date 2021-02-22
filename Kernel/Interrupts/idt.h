#ifndef HYPEROS_INTERRUPTS_IDT_H_
#define HYPEROS_INTERRUPTS_IDT_H_

#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

enum
{
    IDT_TYPE_PRESENT = 1 << 7,
    IDT_TYPE_TASK_GATE = 1 << 0 | 1 << 0,
    IDT_TYPE_INTERRUPT_GATE = 1 << 1 | 1 << 2 | 1 << 3,
    IDT_TYPE_TRAP_GATE = 1 << 0 | 1 << 1 | 1<< 2 | 1 << 3
};

void idt_init(void);
void idt_reload(void);

void idt_register_handler(size_t index, uint8_t flags, void(* handler)(void));
void idt_register_interrupt_handler(size_t index, void(* handler)(void));
void idt_register_trap_handler(size_t index, void(* handler)(void));

#endif