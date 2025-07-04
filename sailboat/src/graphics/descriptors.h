#pragma once
#include "handle.h"

typedef enum descriptor_type
{
    DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER,
    DESCRIPTOR_TYPE_COMBINED_TEXTURE_SAMPLER
} descriptor_type;

gl_handle get_buffer_descriptor_type(descriptor_type type);


typedef struct descriptor
{
    descriptor_type type;
    gl_handle handle;
    u64 binding;
} descriptor;

typedef struct descriptor_set
{
    descriptor descriptors[16];
    u64 descriptorAmount;
} descriptor_set;