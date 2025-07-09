#include <assert.h>
#include "errors.h"
#include "logging.h"
#include "platform.h"
#include "sail_memory.h"
#include "utils/memory_utils.h"

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

void* sail_memory_alloc(u64 size, memory_usage usage)
{
#if defined(DEBUG) || defined(_DEBUG)
    if(usage == MEMORY_UNDEFINED)
        SAIL_LOG_WARN("Undefined allocation usage specified.");

    // todo: align with utils/memory_utils
    s_statistics.totalMemoryAllocated += size;
    s_statistics.memoryUsageAllocated[usage] += size;
#endif

    void* block = platform_alloc(size);
    if(!block)
        SAIL_LOG_FATAL(MEMORY_EXHAUSTED_ERROR_STR);

    return block;
}
void sail_memory_free(void* block, u64 size, memory_usage usage)
{
#if defined(DEBUG) || defined(_DEBUG)
    s_statistics.totalMemoryAllocated -= size;
    s_statistics.memoryUsageAllocated[usage] -= size;
#endif

    platform_free(block);
}

void sail_linear_allocator_initialize(sail_linear_allocator* allocator, u64 capacity)
{
    assert(allocator);
    assert(capacity > 0);

    allocator->buffer = (u8*)sail_memory_alloc(capacity, MEMORY_ARENA);
    allocator->capacity = capacity;
    allocator->currentIndex = 0;
    allocator->externalBuffer = false;
}
void sail_linear_allocator_initialize_external(sail_linear_allocator* allocator, void* buffer, u64 capacity)
{
    assert(allocator);
    assert(buffer);
    assert(capacity > 0);

    allocator->buffer = (u8*)buffer;
    allocator->capacity = capacity;
    allocator->currentIndex = 0;
    allocator->externalBuffer = true;
}

void* sail_linear_allocator_alloc_aligned(sail_linear_allocator* allocator, u64 size, u64 alignment)
{
    assert(size > 0);
    assert(allocator);
    assert(allocator->buffer);

    u64 headAddress = (u64)allocator->buffer + allocator->currentIndex;
    u64 offset = align(headAddress, alignment);
    offset -= headAddress;

    if(offset + size > allocator->capacity)
        return NULL;

    void* ptr = &allocator->buffer[offset];
    allocator->currentIndex = offset + size;
    
    platform_zero_mem(ptr, size);
    return ptr;
}
void* sail_linear_allocator_alloc(sail_linear_allocator* allocator, u64 size)
{
    return sail_linear_allocator_alloc_aligned(allocator, size, 1);
}
void sail_linear_allocator_dealloc(sail_linear_allocator* allocator, u64 size)
{
    assert(allocator);
    assert(size > 0);
    allocator->currentIndex -= size;
}

void sail_linear_allocator_clear(sail_linear_allocator* allocator)
{
    assert(allocator);
    allocator->currentIndex = 0;
}

void sail_linear_allocator_shutdown(sail_linear_allocator* allocator)
{
    if(allocator->externalBuffer)
        SAIL_LOG_WARN("Sail linear allocator is freeing an externally handled resource.");

    sail_memory_free(allocator->buffer, allocator->capacity, MEMORY_ARENA);
    
    allocator->buffer = NULL;
    allocator->currentIndex = 0;
    allocator->capacity = 0;
    allocator->externalBuffer = false;
}
