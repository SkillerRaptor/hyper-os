ENTRY(kernel_main)

SECTIONS
{
	KERNEL_PHYSICAL_OFFSET = 0xFFFFFFFF80000000;
	. = KERNEL_PHYSICAL_OFFSET + 0x200000;

	.stivale2hdr ALIGN(4K) :
	{
		KEEP(*(.stivale2hdr))
	}

	.text ALIGN(4K) :
	{
		KEEP(*(.text*))
	}

	.rodata ALIGN(4K) :
	{
		KEEP(*(.rodata*))
	}

	.data ALIGN(4K) :
	{
		KEEP(*(.data*))
	}

	.bss ALIGN(4K) :
	{
		KEEP(*(COMMON))
		KEEP(*(.bss*))
	}

	.text :
	{
		*(.text)
	}

	.data :
	{
		*(.data)
	}
	
	.bss :
	{
		*(.bss) 
	}
}
