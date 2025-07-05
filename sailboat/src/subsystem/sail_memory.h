#pragma once
#include "defines.h"

typedef enum memory_usage
{
    MEMORY_UNDEFINED,
    MEMORY_STRING,
    MEMORY_ARRAY,

    MEMORY_COUNT
} memory_usage;

void sail_memory_subsystem_initialize();

void* sail_memory_alloc(u64 size, memory_usage usage);

