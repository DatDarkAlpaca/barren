#pragma once
#include "common.h"
#include "pipeline.h"

typedef struct quad_renderer
{
    pipeline pipeline;
    gl_handle vao;
} quad_renderer;

u32 quad_renderer_initialize(quad_renderer* renderer);

void quad_renderer_set_viewport(i32 x, i32 y, i32 width, i32 height);
void quad_renderer_set_scissor(i32 x, i32 y, i32 width, i32 height);

void quad_renderer_begin_render(quad_renderer* renderer, gl_handle target);
void quad_renderer_end_render(quad_renderer* renderer);