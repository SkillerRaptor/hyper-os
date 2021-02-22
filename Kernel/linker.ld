ENTRY(kernel_main)

SECTIONS
{
	KERNEL_PHYSICAL_OFFSET = 0xFFFFFFFF80000000;
	. = KERNEL_PHYSICAL_OFFSET + 0x200000;

    .stivale2hdr :
    {
        KEEP(*(.stivale2hdr))
    }

	.text ALIGN(4K) :
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
