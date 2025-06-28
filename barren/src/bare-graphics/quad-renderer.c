#include <glad/glad.h>

#include "shader.h"
#include "quad-renderer.h"

typedef struct quad_vertex
{
    vec3 position;
} quad_vertex;

static const char* QuadVertexShaderCode = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 a_position"
    "void main()"
    "{"
    "gl_Position = vec4(a_position, 1.0);"
    "}";

static const char* QuadFragmentShaderCode = 
    "#version 330 core\n"
    "layout (location = 0) out vec4 out_color; "
    "void main()"
    "{"
    "out_color = vec4(1.0);"
    "}";

u32 quad_renderer_initialize(quad_renderer* renderer, u64 maxDataCapacity)
{
    // Data:
    u64 quadDataCapacity = maxDataCapacity * sizeof(quad_renderer_data);
    {
        renderer->maxDataCapacity = maxDataCapacity;
        renderer->dataAmount = 0;
        renderer->dataBuffer = (quad_renderer_data*)malloc(quadDataCapacity);
    }
    linear_allocator_initialize(&renderer->dataAllocator, renderer->dataBuffer, quadDataCapacity);

    // Camera:
    camera_initialize(&renderer->camera);

    // Command buffer:
    graphics_command_buffer_initialize(&renderer->commandBuffer);
    renderer->iboType = INDEX_TYPE_UNSIGNED_INT;

    // Shaders:
    shader_creation_result vertexResult = graphics_create_shader(SHADER_VERTEX, QuadVertexShaderCode);
    if(vertexResult.code)
        return vertexResult.code;

    shader_creation_result fragResult = graphics_create_shader(SHADER_FRAGMENT, QuadFragmentShaderCode);
    if(fragResult.code)
        return fragResult.code;

    // Vertex bindings:
    binding_description bindingDescription = {
        .binding = 0,
        .stride = sizeof(quad_vertex),
        .inputRate = INPUT_RATE_VERTEX
    };
    attribute attribute0 = {
        .binding = 0,
        .format = ATTRIBUTE_FORMAT_R32G32B32_SFLOAT,
        .location = 0,
        .normalized = false,
        .offset = 0,
    };

    // Pipeline:
    pipeline_creation_args pipelineArgs = {
        .attributes = { attribute0 },
        .attributeAmount = 1,

        .bindingDescriptions = { bindingDescription },
        .bindingDescriptionAmount = 1,

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

    // Buffers:
    quad_vertex vertices[4] = {
        { .position = { -0.5f, -0.5f, 0.0f } },
        { .position = {  0.5f, -0.5f, 0.0f } },
        { .position = {  0.5f,  0.5f, 0.0f } },
        { .position = { -0.5f,  0.5f, 0.0f } }
    };

    renderer->vbo = graphics_create_buffer(vertices, sizeof(vertices), 
        BUFFER_DYNAMIC_STORAGE
    );
    
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    renderer->ibo = graphics_create_buffer(indices, sizeof(indices), BUFFER_DYNAMIC_STORAGE);

    return SUCCESS;
}

void quad_renderer_add_data(quad_renderer* renderer, quad_renderer_data *data)
{
    linear_allocator_alloc_aligned(&renderer->dataAllocator, sizeof(quad_renderer_data), sizeof(u64));
    ++renderer->dataAmount;
}

void quad_renderer_begin_render(quad_renderer* renderer, gl_handle target)
{
    graphics_begin_render(&renderer->commandBuffer, target);
    graphics_clear();

    graphics_bind_pipeline(&renderer->commandBuffer, &renderer->pipeline);

    graphics_bind_vertex_buffer(&renderer->commandBuffer, renderer->vbo, 0, sizeof(quad_vertex));
    graphics_bind_index_buffer(&renderer->commandBuffer, renderer->ibo, renderer->iboType);
}
void quad_renderer_render(quad_renderer* renderer)
{
    for(u64 i = 0; i < renderer->dataAmount; ++i)
    {
        quad_renderer_data data = renderer->dataBuffer[i];
        data.transform;
        data.rect;

        // graphics_draw(&renderer->commandBuffer, 6, 1, 0, 0);
    }
}
void quad_renderer_end_render(quad_renderer* renderer)
{
    graphics_end_render(&renderer->commandBuffer);
}
