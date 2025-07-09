#pragma once
#include "common.h"
#include "core/scene/scene.h"

typedef u64 view_handle;

struct view;
typedef void(*on_engine_init_clbk)(struct view*);
typedef void(*on_engine_update_clbk)(struct view*, u64);

typedef struct view
{
    on_engine_init_clbk engineInitCallback;
    on_engine_update_clbk engineUpdateCallback;

    scene mainScene;
    scene* currentScene;
    struct context* context;
} view;

void view_initialize(view* view);

ecs_entity_t view_add_entity(view* view);

void view_swap_current_scene(view* view, scene* newScene);