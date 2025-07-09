#include "view_holder.h"
#include "core/common.h"

void view_holder_initialize(view_holder* holder, u64 capacity)
{
    assert(holder);
    assert(capacity > 0);
    
    u64 viewsSize = capacity * sizeof(view);
    holder->views = (view*)sail_memory_alloc(viewsSize, MEMORY_ARENA);

    sail_linear_allocator_initialize_external(&holder->viewAllocator, holder->views, viewsSize);
    platform_zero_mem(holder->viewAllocator.buffer, viewsSize);

    for(u64 i = 0; i < capacity; ++i)
        view_initialize(&holder->views[i]);
}

view_handle view_holder_add(view_holder* holder)
{
    assert(holder);
    assert(holder->viewAllocator.currentIndex + 1 <= holder->viewAllocator.capacity);

    view_handle handle = holder->viewAllocator.currentItem;
    sail_linear_allocator_alloc(&holder->viewAllocator, sizeof(view));

    return handle;
}

view* view_holder_get(view_holder* holder, view_handle handle)
{
    assert(holder);
    assert(holder->views);
    assert(handle >= 0);
    assert(handle < holder->viewAllocator.currentIndex);

    return &holder->views[handle];
}

void view_holder_shutdown(view_holder* holder)
{
    assert(holder);
    assert(holder->views);
    sail_memory_free(holder->views, holder->viewAllocator.capacity, MEMORY_ARENA);
}
