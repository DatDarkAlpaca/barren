#include "scene.h"
#include "context.h"
#include "components.h"

void scene_initialize(scene* scene, context* context)
{
    scene->ecs = ecs_init();
    ecs_set_ctx(scene->ecs, &context, NULL);

    ECS_COMPONENT(scene->ecs, transform_c);
}