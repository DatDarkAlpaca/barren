#pragma once
#include <cglm/cglm.h>
#include "common.h"

typedef struct transform
{
    mat4 data;
} transform;

typedef struct rect
{
    vec2 offset;
    vec2 size;
} rect;

bool is_square_number(u64 number);
 
u64 get_next_square_number(u64 number);
