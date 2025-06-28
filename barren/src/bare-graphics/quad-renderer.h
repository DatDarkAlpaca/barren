#pragma once
#include "common.h"
#include "camera.h"
#include "pipeline.h"
#include "commands.h"
#include "utils/math.h"
#include "utils/linear_allocator.h"

typedef struct quad_renderer_data
{
    transform transform;
    rect rect;
} quad_renderer_data;

typedef struct quad_renderer
{
    command_buffer commandBuffer;
    camera camera;
    
    linear_allocator dataAllocator;
    quad_renderer_data* dataBuffer;
    u64 dataAmount;
    u64 maxDataCapacity;

    pipeline pipeline;
    gl_handle vao;
    gl_handle vbo;
    gl_handle ibo;
    gl_handle mvpHandle;
} quad_renderer;

u32 quad_renderer_initialize(quad_renderer* renderer, u64 maxDataCapacity);

void quad_renderer_add_data(quad_renderer* renderer, quad_renderer_data* data);

void quad_renderer_begin_render(quad_renderer* renderer, gl_handle target);
void quad_renderer_render(quad_renderer* renderer);
void quad_renderer_end_render(quad_renderer* renderer);