#pragma once
#include "view.h"
#include "subsystem/sail_memory.h"

typedef struct view_holder
{
    sail_linear_allocator viewAllocator;
    view* views;
} view_holder;

void view_holder_initialize(view_holder* holder, u64 capacity);

view_handle view_holder_add(view_holder* holder);

view* view_holder_get(view_holder* holder, view_handle handle);

void view_holder_shutdown(view_holder* holder);