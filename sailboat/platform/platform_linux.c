#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "platform.h"

void platform_initialize()
{
    
}

void platform_shutdown()
{
}

void* platform_alloc(u64 size)
{
    void* block = malloc(size);
    assert(block); // TODO: logging
    return block;
}
void platform_free(void* block)
{
    assert(block);
    free(block);
}
void platform_zero_mem(void* block, u64 size)
{
    void* _ = memset(block, 0, size);
}