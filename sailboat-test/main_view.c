#include <stdio.h>
#include <flecs.h>
#include "main_view.h"

typedef struct main_view_data
{
    gl_handle quadTexture;
} main_view_data;

static main_view_data s_data;

static void initialize_textures(view *view, main_view_data* data)
{
    asset_texture* texture = asset_load_default_texture(&view->context->assetHolder, "res/quad.jpg");
    if(!texture)
        return;
}

void main_view_initialize(view *view)
{
    initialize_textures(view, &s_data);

    transform transform;
    {
        transform_initialize(&transform);

        vec3 scale = { 100.0f, 100.0f, 1.f };
        transform_set_scale(&transform, scale);
    }
    
    ecs_entity_t entity = ecs_new(view->scene.ecs); 
    ecs_set(view->scene.ecs, entity, transform_component, { .transform = transform });
    ecs_set(view->scene.ecs, entity, quad_texture_component, { .textureHandle = 0 });
}
