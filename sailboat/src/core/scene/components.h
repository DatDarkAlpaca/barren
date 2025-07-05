#pragma once
#include <flecs.h>
#include "utils/math.h"
#include "graphics/handle.h"

typedef struct
{
    transform transform;
} transform_component;
extern ECS_COMPONENT_DECLARE(transform_component);

typedef struct
{
    gl_handle textureHandle;
} quad_texture_component;
extern ECS_COMPONENT_DECLARE(quad_texture_component);