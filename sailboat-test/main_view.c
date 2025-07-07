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

void main_view_initialize(view *view)
{
    initialize_textures(view, &s_data);

    transform transform;
    {
        transform_initialize(&transform);

        vec3 position = {100.0f, 100.f, 0.0f};
        transform_set_position(&transform, position);

        vec3 scale = { 100.0f, 100.0f, 1.0f };
        transform_set_scale(&transform, scale);
    }
    
    ecs_entity_t entity = view_add_entity(view);
    ecs_set(view->scene.ecs, entity, transform_component, { .transform = transform });
    ecs_set(view->scene.ecs, entity, quad_texture_component, { .textureHandle = s_data.quadTexture });
}
