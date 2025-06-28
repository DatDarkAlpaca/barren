#pragma once
#include <flecs.h>

typedef struct scene
{
    ecs_world_t* ecs;
} scene;

typedef struct entity
{
    ecs_entity_t handle;
} entity;

void scene_initialize(scene* scene);