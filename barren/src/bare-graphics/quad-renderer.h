#pragma once
#include "common.h"
#include "pipeline.h"
#include "utils/math.h"
#include "utils/linear_allocator.h"

typedef struct quad_renderer_data
{
    transform transform;
    rect rect;
} quad_renderer_data;

typedef struct quad_renderer
{
    linear_allocator dataAllocator;
    quad_renderer_data* dataBuffer;
    u64 dataAmount;
    u64 maxDataCapacity;

    pipeline pipeline;
    gl_handle vao;
    u32 __padding;
} quad_renderer;

u32 quad_renderer_initialize(quad_renderer* renderer, u64 maxDataCapacity);

void quad_renderer_set_viewport(i32 x, i32 y, i32 width, i32 height);
void quad_renderer_set_scissor(i32 x, i32 y, i32 width, i32 height);

void quad_renderer_add_data(quad_renderer* renderer, quad_renderer_data* data);

void quad_renderer_begin_render(quad_renderer* renderer, gl_handle target);
void quad_renderer_render(quad_renderer* renderer);
void quad_renderer_end_render(quad_renderer* renderer);