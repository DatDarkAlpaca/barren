#include <stdio.h>
#include <flecs.h>
#include "main_view.h"

void main_view_initialize(view *view)
{
    SAIL_LOG_WARN("HI");

    transform transform;
    {
        transform_initialize(&transform);

        vec3 scale = { 100.0f, 100.0f, 1.f };
        transform_set_scale(&transform, scale);
    }
    
    ecs_entity_t entity = ecs_new(view->scene.ecs); 
    ecs_set(view->scene.ecs, entity, transform_component, { .transform = transform });
}
