#pragma once
#include <cglm/cglm.h>
#include "common.h"

typedef struct transform
{
    vec3 position;
    vec3 rotation;
    vec3 scale;
    mat4 data;
} transform;
void transform_initialize(transform* transform);
void transform_set_position(transform* transform, vec3 position);
void transform_set_rotation(transform* transform, vec3 rotation);
void transform_set_scale(transform* transform, vec3 scale);
void update_transform_data(transform* transform);

typedef struct rect
{
    vec2 offset;
    vec2 size;
} rect;

bool is_square_number(u64 number);
 
u64 get_next_square_number(u64 number);
