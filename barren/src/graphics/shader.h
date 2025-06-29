#pragma once
#include "common.h"
#include "handle.h"

typedef enum shader_type
{
    SHADER_VERTEX,
    SHADER_FRAGMENT
} shader_type;

typedef struct shader_creation_result
{
    char message[512];
    u32 code;
    gl_handle handle;
} shader_creation_result;

shader_creation_result graphics_create_shader(shader_type type, const char* const source);
void graphics_destroy_shader(gl_handle shaderHandle);