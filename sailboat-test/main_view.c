#include <stdio.h>
#include <flecs.h>
#include "main_view.h"

typedef struct main_view_data
{
    gl_handle quadTexture;
} main_view_data;

static main_view_data s_data;

static void initialize_textures(view* view, main_view_data* data)
{
    data->quadTexture = engine_create_texture(view->context, "res/quad.jpg", 3);
}

static void main_view_move(ecs_iter_t* it)
{
    assert(it);
    context* context = ecs_get_ctx(it->world);

    transform_component* transformComponent = ecs_field(it, transform_component, 0);
    assert(transformComponent);

    static f32 totalTime = 0;

    f32 time = context->frameDeltaTime;
    totalTime += time;

    for (int i = 0; i < it->count; ++i) 
    {
        transform* t = &transformComponent[i].transform;

        vec3 newPosition = { cosf(totalTime) * 100.f - 100.0f, sinf(totalTime) * 100.0f, 0.0f };
        //vec3 newPosition = { time, 0.0f, 0.0f };        
        transform_set_position(t, newPosition);
    }
}

void main_view_initialize(view *view)
{
    initialize_textures(view, &s_data);

    transform transform;
    {
        transform_initialize(&transform);

        vec3 position = {200.0f, 100.f, 0.0f};
        transform_set_position(&transform, position);

        vec3 scale = { 100.0f, 100.0f, 1.0f };
        transform_set_scale(&transform, scale);
    }
    
    ecs_entity_t entity = view_add_entity(view);
    ecs_set(view->currentScene->ecs, entity, transform_component, { .transform = transform });
    ecs_set(view->currentScene->ecs, entity, quad_texture_component, { .textureHandle = s_data.quadTexture });

    ECS_SYSTEM(view->currentScene->ecs, main_view_move, EcsOnUpdate, transform_component);
}