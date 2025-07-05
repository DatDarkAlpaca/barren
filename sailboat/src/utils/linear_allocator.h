#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "utils/math.h"
#include "utils/memory_utils.h"

typedef struct linear_allocator
{
    u8* buffer;
    u64 bufferCapacity;
    u64 currentIndex;
} linear_allocator;

void linear_allocator_initialize(linear_allocator* allocator, void* buffer, u64 capacity);

void* linear_allocator_alloc_aligned(linear_allocator* allocator, u64 size, u64 alignment);
void* linear_allocator_alloc(linear_allocator* allocator, u64 size);
void linear_allocator_dealloc(linear_allocator* allocator, u64 size);

void linear_allocator_clear(linear_allocator* allocator);