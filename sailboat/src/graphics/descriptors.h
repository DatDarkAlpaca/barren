#pragma once
#include "handle.h"
#define BAR_PIPELINE_MAX_DESCRIPTORS    16

typedef enum descriptor_type
{
    DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER,
    DESCRIPTOR_TYPE_COMBINED_TEXTURE_SAMPLER
} descriptor_type;

gl_handle get_descriptor_type(descriptor_type type);

typedef struct descriptor
{
    descriptor_type type;
    gl_handle handle;
    u64 binding;
} descriptor;

typedef struct descriptor_set
{
    descriptor descriptors[BAR_PIPELINE_MAX_DESCRIPTORS];
    u64 descriptorAmount;
} descriptor_set;

void graphics_update_descriptor_resource(descriptor_set* set, gl_handle handle, descriptor_type type, u32 binding, u32 descriptorIndex);