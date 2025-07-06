#include <assert.h>
#include "errors.h"
#include "logging.h"
#include "platform.h"
#include "sail_memory.h"

typedef struct memory_statistics
{
    u64 totalMemoryAllocated;
    u64 memoryUsageAllocated[MEMORY_COUNT];
} memory_statistics;

static struct memory_statistics s_statistics;

void sail_memory_subsystem_initialize()
{
    platform_zero_mem(&s_statistics, sizeof(memory_statistics));
}

void *sail_memory_alloc(u64 size, memory_usage usage)
{
    if(usage == MEMORY_UNDEFINED)
        SAIL_LOG_WARN("Undefined allocation usage specified.");
    
    // todo: align with utils/memory_utils
    s_statistics.totalMemoryAllocated += size;
    s_statistics.memoryUsageAllocated[usage] += size;

    void* block = platform_alloc(size);
    if(!block)
        SAIL_LOG_FATAL(MEMORY_EXHAUSTED_ERROR_STR);

    assert(block); // todo: error

    return block;
}