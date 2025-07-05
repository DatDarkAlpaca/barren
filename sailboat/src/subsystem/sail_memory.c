#include <string.h>
#include <stdlib.h>

#include "memory.h"
#include "defines.h"
#include "sail_memory.h"

typedef struct memory_statistics
{
    u64 totalMemoryAllocated;
    u64 memoryUsageAllocated[MEMORY_COUNT];
} memory_statistics;

static struct memory_statistics s_statistics;

void sail_memory_subsystem_initialize()
{
    memset(&s_statistics, 0, sizeof(memory_statistics));
}

void *sail_memory_alloc(u64 size, memory_usage usage)
{
    if(usage == MEMORY_UNDEFINED)
    {
        // TODO: logging
    }

    // todo: align with utils/memory_utils
    s_statistics.totalMemoryAllocated += size;
    s_statistics.memoryUsageAllocated[usage] += size;

    void* block = malloc(size);
    assert(block); // todo: error

    return block;
}