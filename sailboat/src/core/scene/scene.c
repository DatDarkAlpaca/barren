#include "scene.h"
#include "context.h"
#include "components.h"

#include "core/system/render_system.h"

static void define_engine_components(ecs_world_t* world)
{
    ECS_COMPONENT_DEFINE(world, transform_component);

    ECS_COMPONENT_DEFINE(world, quad_texture_component);
}

static void define_engine_systems(ecs_world_t* world)
{
    ECS_SYSTEM(world, system_render_quads, EcsOnUpdate, transform_component, quad_texture_component);
}

void scene_initialize(scene* scene, context* context)
{
    assert(scene);
    assert(context);

    scene->ecs = ecs_init();
    ecs_set_ctx(scene->ecs, context, NULL);

    define_engine_components(scene->ecs);
    define_engine_systems(scene->ecs);
}