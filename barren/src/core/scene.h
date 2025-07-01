#pragma once
#include <flecs.h>
#define BAR_SCENE_MAX   256

typedef struct entity
{
    ecs_entity_t handle;
} entity;

typedef struct scene
{
    ecs_world_t* ecs;
} scene;

struct context;
void scene_initialize(scene* scene, struct context* context);