#pragma once
#include <stdbool.h>
#include "handle.h"
#include "descriptors.h"
#define BAR_PIPELINE_MAX_ATTRIBUTES         16
#define BAR_PIPELINE_MAX_BINDINGS           4
#define BAR_PIPELINE_MAX_DESCRIPTOR_SETS    4

// Rasterizer:
typedef enum pipeline_front_face
{
    FRONT_FACE_CW,
    FRONT_FACE_CCW
} pipeline_front_face;

typedef enum pipeline_polygon_mode
{
    POLYGON_MODE_POINT,
    POLYGON_MODE_LINE,
    POLYGON_MODE_FILL,
} pipeline_polygon_mode;

typedef enum pipeline_cull_face
{
    CULL_FRONT,
    CULL_BACK,
    CULL_FRONT_AND_BACK
} pipeline_cull_face;

typedef enum pipeline_topology
{
    TOPOLOGY_POINTS,
    TOPOLOGY_LINES,
    TOPOLOGY_TRIANGLES
} pipeline_topology;

// Attributes:
typedef enum pipeline_vertex_input_rate
{
    INPUT_RATE_VERTEX = 0,
    INPUT_RATE_INSTANCE
} pipeline_vertex_input_rate;

typedef enum attribute_format
{
    ATTRIBUTE_FORMAT_R32_SFLOAT,             // FLOAT
    ATTRIBUTE_FORMAT_R64_SFLOAT,             // DOUBLE
    ATTRIBUTE_FORMAT_R32G32_SFLOAT,          // VEC2
    ATTRIBUTE_FORMAT_R32G32B32_SFLOAT,       // VEC3
    ATTRIBUTE_FORMAT_R32G32B32A32_SFLOAT,    // VEC4
    ATTRIBUTE_FORMAT_R32G32_SINT,            // IVEC2
    ATTRIBUTE_FORMAT_R32G32B32A32_UINT,      // UVEC4
} attribute_format;

gl_handle get_attribute_format(attribute_format format);
u64 get_attribute_format_size(attribute_format format);

typedef struct binding_description
{
    u32 binding;
    u32 stride;
    pipeline_vertex_input_rate inputRate;
} binding_description;

typedef struct attribute
{
    u32 binding;
    u32 location;
    attribute_format format;
    u32 offset;
    bool normalized;
} attribute;

typedef struct pipeline_creation_args
{
    binding_description bindingDescriptions[BAR_PIPELINE_MAX_BINDINGS];
    attribute attributes[BAR_PIPELINE_MAX_ATTRIBUTES];
    descriptor_set descriptorSets[BAR_PIPELINE_MAX_DESCRIPTOR_SETS];
    u64 attributeAmount;
    u64 bindingDescriptionAmount;
    u64 descriptorSetAmount;

    gl_handle vertexShader;
    gl_handle fragmentShader;
    
    pipeline_topology topology;
    pipeline_front_face frontFace;
    pipeline_polygon_mode polygonMode;
    pipeline_cull_face cullFace;
} pipeline_creation_args;

typedef struct pipeline
{
    binding_description bindingDescriptions[BAR_PIPELINE_MAX_BINDINGS];
    attribute attributes[BAR_PIPELINE_MAX_ATTRIBUTES];
    descriptor_set descriptorSets[BAR_PIPELINE_MAX_DESCRIPTOR_SETS];
    u64 attributeAmount;
    u64 bindingDescriptionAmount;
    u64 descriptorSetAmount;

    gl_handle handle;

    pipeline_topology topology;
    pipeline_front_face frontFace;
    pipeline_polygon_mode polygonMode;
    pipeline_cull_face cullFace;
} pipeline;

typedef struct pipeline_creation_result
{
    pipeline pipeline;
    char message[512];
    u32 code;
} pipeline_creation_result;

pipeline_creation_result graphics_create_pipeline(const pipeline_creation_args* const args);
void graphics_destroy_pipeline(pipeline* pipeline);