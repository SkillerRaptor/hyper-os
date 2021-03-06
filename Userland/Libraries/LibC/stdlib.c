#include <stdlib.h>

#include <string.h>
#include <AK/logger.h>

void abort()
{
	// TODO: Abnormally terminate the process as if by SIGABRT.

	while (1);
}

void* malloc(size_t size)
{
	(void) size;
	error("LibC (stdlib.c): malloc(size_t size) is not implemented!");
	return NULL;
}

void* calloc(size_t num, size_t size)
{
	(void) num;
	(void) size;
	error("LibC (stdlib.c): calloc(size_t num, size_t size) is not implemented!");
	return NULL;
}

void* realloc(void* ptr, size_t size)
{
	(void) ptr;
	(void) size;
	error("LibC (stdlib.c): realloc(void* ptr, size_t size) is not implemented!");
	return NULL;
}

void free(void* ptr)
{
	(void) ptr;
	error("LibC (stdlib.c): free(void* ptr) is not implemented!");
}