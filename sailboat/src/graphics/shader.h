#pragma once
#include "common.h"
#include "handle.h"

typedef enum shader_type
{
    SHADER_VERTEX,
    SHADER_FRAGMENT
} shader_type;

gl_handle graphics_create_shader(shader_type type, const char* const source);
void graphics_destroy_shader(gl_handle shaderHandle);