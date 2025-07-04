#include "render_system.h"
#include "context.h"

void system_render_quads(ecs_iter_t* it)
{
    context* context = ecs_get_ctx(it->world);
    
    assert(it);    
    assert(context);

    quad_renderer* renderer = &context->quadRenderer;
    transform_c* transform = ecs_field(it, transform_c, 0);
    for (int i = 0; i < it->count; i++)
    {
        
    }
}
