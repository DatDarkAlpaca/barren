#include <glad/glad.h>
#include <assert.h>
#include "commands.h"

void graphics_command_buffer_initialize(command_buffer *commandBuffer)
{
    glCreateVertexArrays(1, &commandBuffer->vao);
}

void graphics_begin_render(command_buffer *commandBuffer, gl_handle target)
{
    glBindVertexArray(commandBuffer->vao);
    glBindFramebuffer(GL_FRAMEBUFFER, target);
}
void graphics_begin_render_default(command_buffer *commandBuffer)
{
    graphics_begin_render(commandBuffer, 0);
}

void graphics_clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void graphics_set_clear_color(f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void graphics_set_viewport(i32 x, i32 y, i32 width, i32 height)
{
    glViewport(x, y, width, height);
}
void graphics_set_scissor(i32 x, i32 y, i32 width, i32 height)
{
    glScissor(x, y, width, height);
}

void graphics_bind_pipeline(command_buffer *commandBuffer, pipeline *pipeline)
{
    assert(commandBuffer->vao != invalid_handle);
    assert(pipeline->handle != invalid_handle);

    commandBuffer->pipelineTopology = pipeline->topology;
    glUseProgram(pipeline->handle);

    POLYGON_MODE_POINT,
    POLYGON_MODE_LINE,
    POLYGON_MODE_FILL,

    glFrontFace(pipeline->frontFace == FRONT_FACE_CW ? GL_CW : GL_CCW);

    gl_handle polygonMode;
    switch(pipeline->polygonMode)
    {
        case POLYGON_MODE_FILL:
            polygonMode = GL_FILL;

        case POLYGON_MODE_LINE:
            polygonMode = GL_LINE;

        case POLYGON_MODE_POINT:
            polygonMode = GL_POINT;

        default:
        {
            // TODO: error
        }
    }
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    gl_handle cullMode;
    switch(pipeline->cullFace)
    {
        case CULL_BACK:
            cullMode = GL_BACK;

        case CULL_FRONT:
            cullMode = GL_FRONT;

        case CULL_FRONT_AND_BACK:
            cullMode = GL_FRONT_AND_BACK;

        default:
        {
            // TODO: error
        }
    }
	glCullFace(cullMode);

    for(u64 i = 0; i < pipeline->bindingDescriptionAmount; ++i)
    {
        binding_description* description = &pipeline->bindingDescriptions[i];

        for(u64 j = 0; j < pipeline->attributeAmount; ++j)
        {
            attribute* attribute = &pipeline->attributes[j];

            if (attribute->binding != description->binding)
				continue;

            glEnableVertexArrayAttrib(commandBuffer->vao, attribute->location);
            glVertexArrayAttribFormat(
                commandBuffer->vao,
                attribute->location,
                (i32)get_attribute_format_size(attribute->format),
                get_attribute_format(attribute->format),
                attribute->normalized,
                attribute->offset
            );

            glVertexArrayAttribBinding(commandBuffer->vao, attribute->location, description->binding);

            u32 divisor = description->inputRate == INPUT_RATE_VERTEX ? 0 : 1;
			glVertexArrayBindingDivisor(commandBuffer->vao, description->binding, divisor);
        }
    }
}
void graphics_bind_descriptor_set(gl_handle descriptorSetHandle)
{
}
void graphics_bind_vertex_buffer(command_buffer *commandBuffer, gl_handle bufferHandle, u32 binding, u32 stride)
{
    assert(commandBuffer->vao != invalid_handle);
    assert(bufferHandle != invalid_handle);

    glVertexArrayVertexBuffer(commandBuffer->vao, binding, bufferHandle, 0, stride);
}
void graphics_bind_index_buffer(command_buffer *commandBuffer, gl_handle bufferHandle, buffer_index_type indexType)
{
    assert(commandBuffer->vao != invalid_handle);
    assert(bufferHandle != invalid_handle);

    glVertexArrayElementBuffer(commandBuffer->vao, bufferHandle);
}

void graphics_draw(command_buffer *commandBuffer, u32 vertexCount, u32 instanceCount, u32 firstVertex, u32 firstInstance)
{
    assert(instanceCount >= 1);
    assert(firstVertex >= 0);
    assert(firstInstance >= 0);
    assert(vertexCount >= 0);

    gl_handle topology;
    switch(commandBuffer->pipelineTopology)
    {
        case TOPOLOGY_POINTS:
            topology = GL_POINTS;

        case TOPOLOGY_LINES:
            topology = GL_LINES;

        case TOPOLOGY_TRIANGLES:
            topology = GL_TRIANGLES;
    }

    if (instanceCount == 1)
		glDrawArrays(topology, firstVertex, vertexCount);
	else
		glDrawArraysInstanced(topology, firstVertex, vertexCount, instanceCount);
}

void graphics_end_render(command_buffer *commandBuffer)
{
    graphics_begin_render_default(commandBuffer);
}
