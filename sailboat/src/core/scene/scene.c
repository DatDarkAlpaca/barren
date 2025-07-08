#include "scene.h"
#include "context.h"
#include "components.h"

#include "core/system/render_system.h"

static scene_handle s_currentHandle = 0;

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
    if(!scene->ecs)
    {
        SAIL_LOG_FATAL("Failed to initialize scene's world object");
        return;
    }

    ecs_set_ctx(scene->ecs, context, NULL);

    scene->id = s_currentHandle;
    ++s_currentHandle;

    define_engine_components(scene->ecs);
    define_engine_systems(scene->ecs);
}