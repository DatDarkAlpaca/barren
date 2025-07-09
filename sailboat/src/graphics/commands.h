#pragma once
#include "common.h"
#include "buffer.h"
#include "pipeline.h"

typedef struct command_buffer
{
    gl_handle vao;
    gl_handle pipelineTopology;
    buffer_index_type indexType;
} command_buffer;

void graphics_command_buffer_initialize(command_buffer* commandBuffer);

void graphics_begin_render(command_buffer* commandBuffer, gl_handle target);
void graphics_begin_render_default(command_buffer* commandBuffer);

void graphics_clear();
void graphics_set_clear_color(f32 r, f32 g, f32 b, f32 a);

void graphics_set_viewport(i32 x, i32 y, i32 width, i32 height);
void graphics_set_scissor(i32 x, i32 y, i32 width, i32 height);

void graphics_bind_pipeline(command_buffer* commandBuffer, pipeline* pipeline);
void graphics_bind_descriptor_set(command_buffer* commandBuffer, descriptor_set* set);
void graphics_bind_vertex_buffer(command_buffer* commandBuffer, gl_handle bufferHandle, u32 binding, u32 stride);
void graphics_bind_index_buffer(command_buffer* commandBuffer, gl_handle bufferHandle, buffer_index_type indexType);

void graphics_draw(command_buffer* commandBuffer, u32 vertexCount, u32 instanceCount, u32 firstVertex, u32 firstInstance);
void graphics_draw_indexed(command_buffer* commandBuffer, u32 indexCount, u32 instanceCount, u32 firstVertex, u32 firstInstance);

void graphics_end_render(command_buffer* commandBuffer);