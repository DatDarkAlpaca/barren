#pragma once
#include "defines.h"

typedef enum memory_usage
{
    MEMORY_UNDEFINED,
    MEMORY_STRING,
    MEMORY_ARRAY,
    MEMORY_ARENA,

    MEMORY_TEXTURE,

    MEMORY_COUNT
} memory_usage;

void sail_memory_subsystem_initialize();

void* sail_memory_alloc(u64 size, memory_usage usage);
void sail_memory_free(void* block, u64 size, memory_usage usage);

typedef struct sail_linear_allocator
{
    u8* buffer;
    u64 capacity;
    u64 currentIndex;
    bool externalBuffer;
} sail_linear_allocator;

void sail_linear_allocator_initialize(sail_linear_allocator* allocator, u64 capacity);
void sail_linear_allocator_initialize_external(sail_linear_allocator* allocator, void* buffer, u64 capacity);

void* sail_linear_allocator_alloc_aligned(sail_linear_allocator* allocator, u64 size, u64 alignment);
void* linear_allocator_alloc(sail_linear_allocator* allocator, u64 size);
void sail_linear_allocator_dealloc(sail_linear_allocator* allocator, u64 size);

void sail_linear_allocator_clear(sail_linear_allocator* allocator);

void sail_linear_allocator_shutdown(sail_linear_allocator* allocator);
