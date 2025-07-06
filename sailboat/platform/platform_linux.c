#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "common.h"
#include "platform.h"

void platform_initialize()
{
    
}
void platform_shutdown()
{
}

void platform_breakpoint()
{
    raise(SIGINT);
}

void* platform_alloc(u64 size)
{
    void* block = malloc(size);
    if(!block)
        SAIL_LOG_FATAL(MEMORY_EXHAUSTED_ERROR_STR);
    
    return block;
}
void platform_free(void* block)
{
    assert(block);
    free(block);
}
void platform_zero_mem(void* block, u64 size)
{
    memset(block, 0, size);
}