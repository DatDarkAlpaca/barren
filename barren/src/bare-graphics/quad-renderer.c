#include <glad/glad.h>
#include "quad-renderer.h"
#include "shader.h"

static const char* QuadVertexShaderCode = 
    "#version 330 core\n"
    "void main()"
    "{"
    "gl_Position = vec4(1.0);"
    "}";

static const char* QuadFragmentShaderCode = 
    "#version 330 core\n"
    "layout (location = 0) out vec4 out_color; "
    "void main()"
    "{"
    "out_color = vec4(1.0);"
    "}";

u32 quad_renderer_initialize(quad_renderer *renderer)
{
    // VAO:
    glCreateVertexArrays(1, &renderer->vao);

    // Shaders:
    shader_creation_result vertexResult = graphics_create_shader(SHADER_VERTEX, QuadVertexShaderCode);
    if(vertexResult.code)
        return vertexResult.code;

    shader_creation_result fragResult = graphics_create_shader(SHADER_FRAGMENT, QuadFragmentShaderCode);
    if(fragResult.code)
        return fragResult.code;

    // Pipeline:
    pipeline_creation_args pipelineArgs = {
        .cullFace = CULL_FRONT,
        .frontFace = FRONT_FACE_CCW,
        .polygonMode = POLYGON_MODE_FILL,
        .vertexShader = vertexResult.handle,
        .fragmentShader = fragResult.handle
    };
    pipeline_creation_result pipelineResult = graphics_create_pipeline(&pipelineArgs);
    if(pipelineResult.code)
        return pipelineResult.code;

    renderer->pipeline = pipelineResult.pipeline;
    return SUCCESS;
}

void quad_renderer_set_viewport(i32 x, i32 y, i32 width, i32 height)
{
    glViewport(x, y, width, height);   
}
void quad_renderer_set_scissor(i32 x, i32 y, i32 width, i32 height)
{
    glScissor(x, y, width, height);
}

void quad_renderer_begin_render(quad_renderer *renderer, gl_handle target)
{
    glBindVertexArray(renderer->vao);
    glBindFramebuffer(GL_FRAMEBUFFER, target);
}
void quad_renderer_end_render(quad_renderer *renderer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
