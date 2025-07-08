#pragma once
#include <flecs.h>
#include "defines.h"
#define BAR_SCENE_MAX   256

typedef struct entity
{
    ecs_entity_t handle;
} entity;

typedef u64 scene_handle;

typedef struct scene
{
    ecs_world_t* ecs;
    scene_handle id;
} scene;

struct context;
void scene_initialize(scene* scene, struct context* context);