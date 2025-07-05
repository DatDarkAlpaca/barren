#pragma once
#include <flecs.h>
#include "utils/math.h"

typedef struct
{
    transform transform;
} transform_c;

extern ECS_COMPONENT_DECLARE(transform_c);