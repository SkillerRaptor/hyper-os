#include <LibC/stdio.h>

#include "Core/GDT.h"
#include "Core/IDT.h"
#include "Core/PIC.h"
#include "Core/Terminal.h"

__BEGIN_DECLS
void KernelEarlyMain()
{
	GDT::Get().CreateBasicDescriptor();
	GDT::Get().Install();

	PIC::Get().ReMap(0x20, 0x28);

	IDT::Get().CreateBasicTables();
	IDT::Get().Install();
}

void KernelInit()
{
	Terminal::Initialize();
}

void KernelMain()
{
	printf("Hello, Kernel World!\n");
}
__END_DECLS