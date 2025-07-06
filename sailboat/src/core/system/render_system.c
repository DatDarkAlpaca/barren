#include "render_system.h"

#include "graphics/renderer/quad-renderer.h"
#include "core/scene/components.h"
#include "core/scene/scene.h"
#include "context.h"

void system_render_quads(ecs_iter_t* it)
{
    context* context = ecs_get_ctx(it->world);
    quad_renderer* renderer = &context->quadRenderer;

    assert(it);    
    assert(context);
    assert(renderer);

    transform_component* transform = ecs_field(it, transform_component, 0);
    quad_texture_component* texture  = ecs_field(it, quad_texture_component, 1);
    assert(transform);
    
    for (int i = 0; i < it->count; ++i) 
    {
        quad_renderer_data data =
        {
            .transform = transform[i].transform,
            .textureHandle = texture->textureHandle
        };

        quad_renderer_add_data(renderer, &data);
    }

    quad_renderer_begin_render(renderer, 0);
    quad_renderer_render(renderer);
    quad_renderer_end_render(renderer);

    quad_renderer_clear_data(renderer);
}
