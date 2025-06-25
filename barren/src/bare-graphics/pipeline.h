#pragma once
#include "handle.h"

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

typedef struct pipeline_creation_args
{
    gl_handle vertexShader;
    gl_handle fragmentShader;
    
    pipeline_front_face frontFace;
    pipeline_polygon_mode polygonMode;
    pipeline_cull_face cullFace;
} pipeline_creation_args;

typedef struct pipeline
{
    gl_handle handle;

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