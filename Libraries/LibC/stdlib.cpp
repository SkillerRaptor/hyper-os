#include <LibC/stdlib.h>

#include <LibC/stdio.h>

void abort()
{
#if defined(__is_libk)
    // TODO: Add proper kernel panic.
    printf("Kernel: panic: abort()\n");
#else
    // TODO: Abnormally terminate the process as if by SIGABRT.
    printf("abort()\n");
#endif

    while (true);
}