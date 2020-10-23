#include <LibC/stdio.h>

#include "Core/Terminal.h"

__BEGIN_DECLS
void KernelInit()
{
    Terminal::Initialize();
}

void KernelMain()
{
    printf("Hello, Kernel World!\n");
}
__END_DECLS