#pragma once
#include "common.h"
#include "scene.h"

typedef u64 view_handle;

struct view;
typedef void(*on_engine_init_clbk)(struct view*);
typedef void(*on_engine_update_clbk)(struct view*, u64);

typedef struct view
{
    on_engine_init_clbk engineInitCallback;
    on_engine_update_clbk engineUpdateCallback;

    scene scene;
    struct context* context;
} view;

typedef struct view_holder
{
    view* views;
    u64 currentView;
    u64 capacity;
} view_holder;

void view_holder_initialize(view_holder* holder, u64 capacity);

view_handle view_holder_add(view_holder* holder);

view* view_holder_get(view_holder* holder, view_handle handle);
