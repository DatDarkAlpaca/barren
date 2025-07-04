#include "linear_allocator.h"

void linear_allocator_initialize(linear_allocator* allocator, void* buffer, u64 capacity)
{
    allocator->buffer = (u8*)buffer;
    allocator->bufferCapacity = capacity;
    allocator->currentIndex = 0;
}

void *linear_allocator_alloc_aligned(linear_allocator* allocator, u64 size, u64 alignment)
{
    u64 headAddress = (u64)allocator->buffer + allocator->currentIndex;
    u64 offset = align(headAddress, alignment);
    offset -= headAddress;

    if(offset + size > allocator->bufferCapacity)
        return NULL;

    void* ptr = &allocator->buffer[offset];
    allocator->currentIndex = offset + size;
    memset(ptr, 0, size);
    return ptr;
}
void *linear_allocator_alloc(linear_allocator* allocator, u64 size)
{
    return linear_allocator_alloc_aligned(allocator, size, 1);
}
void linear_allocator_dealloc(linear_allocator* allocator, u64 size)
{
    allocator->currentIndex -= size;
}

void linear_allocator_clear(linear_allocator* allocator)
{
    allocator->currentIndex = 0;
}
