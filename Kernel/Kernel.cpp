#include <LibC/stdio.h>

#include "Core/GDT.h"
#include "Core/Terminal.h"

__BEGIN_DECLS
void KernelEarlyMain()
{
    GDT::Get().CreateBasicDescriptor();
    GDT::Get().Install();
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