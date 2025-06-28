#include "scene.h"
#include "components.h"

void scene_initialize(scene* scene)
{
    scene->ecs = ecs_init();
    ECS_COMPONENT(scene->ecs, transform_c);
}