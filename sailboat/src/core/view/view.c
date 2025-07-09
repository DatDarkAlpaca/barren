#include "view.h"

void view_initialize(view* view)
{
    view->currentScene = &view->mainScene;
}

ecs_entity_t view_add_entity(view* view)
{
    return ecs_new(view->currentScene->ecs);
}

void view_swap_current_scene(view* view, scene* newScene)
{
    view->currentScene = newScene;
}
