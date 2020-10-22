#include <LibC/stdio.h>

#include "Core/Terminal.h"

__BEGIN_DECLS
void KernelMain()
{
    Terminal::Initialize();

    printf("Hello, Kernel World!\n");
}
__END_DECLS