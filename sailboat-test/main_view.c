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
    asset_texture* texture = asset_load_texture_spec_channels(&view->context->assetHolder, "res/quad.jpg", 3);
    if(!texture)
        return SAIL_LOG_ERROR("Failed to load image");

    texture_args args = { 0 };
    {
        args.width = texture->width;
        args.height = texture->height;
        args.format = TEXTURE_FORMAT_RGB8_UNORM;
        args.type = TEXTURE_TYPE_2D;
    }

    data->quadTexture = graphics_create_texture(&args);
    if(data->quadTexture == invalid_handle)
        return SAIL_LOG_ERROR("Failed to create texture");

    graphics_update_texture(data->quadTexture, TEXTURE_TYPE_2D, texture);
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
    
    ecs_entity_t entity = ecs_new(view->scene.ecs); 
    ecs_set(view->scene.ecs, entity, transform_component, { .transform = transform });
    ecs_set(view->scene.ecs, entity, quad_texture_component, { .textureHandle = s_data.quadTexture });
}
