#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

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
    assert(size > 0);

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
    assert(block);
    assert(size > 0);
    memset(block, 0, size);
}

void* platform_create_thread(thread_routine routine, void* argument)
{
    pthread_t thread;
    int result = pthread_create(&thread, NULL, routine, argument);

    if(result)
    {
        SAIL_LOG_ERROR("Thread creation failed with code: %d", result);
        return NULL;
    }

    return (void*)thread;
}