#ifndef HYPEROS_KERNEL_SYSTEM_GDT_H_
#define HYPEROS_KERNEL_SYSTEM_GDT_H_

#define KERNEL_CODE_SELECTOR 0x8
#define KERNEL_DATA_SELECTOR 0x10

void gdt_init(void);
void gdt_reload(void);

#endif // HYPEROS_KERNEL_SYSTEM_GDT_H_
