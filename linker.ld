ENTRY(KernelMain)

SECTIONS
{
    KernelPhysicalOffset = 0xFFFFFFFF80000000;
    . = KernelPhysicalOffset + 0x200000;
	
    .stivale2hdr :
    {
        KEEP(*(.stivale2hdr))
    }

    .text : ALIGN(4K)
    {
        *(.text*)
    }

    .rodata ALIGN(4K) :
    {
        *(.rodata*)
    }

    .data ALIGN(4K) :
    {
        *(.data*)
    }

    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss*)
    }
}