#include "view.h"

void view_holder_initialize(view_holder* holder, u64 capacity)
{
    assert(holder);
    
    holder->views = (view*)calloc(sizeof(view), capacity);
    assert(holder->views);

    holder->capacity = capacity;
    holder->currentView = 0;
}

view_handle view_holder_add(view_holder* holder)
{
    assert(holder);
    assert(holder->currentView + 1 <= holder->capacity);

    view_handle handle = holder->currentView;
    ++holder->currentView;

    return handle;
}

view* view_holder_get(view_holder* holder, view_handle handle)
{
    assert(holder);
    assert(holder->views);
    assert(handle >= 0);
    assert(handle < holder->currentView);

    return &holder->views[handle];
}
