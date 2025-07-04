#include <glad/glad.h>

#include "shader.h"
#include "descriptors.h"
#include "quad-renderer.h"

typedef struct quad_vertex
{
    vec3 position;
} quad_vertex;

typedef struct quad_mvp
{
    mat4 model;
    mat4 view;
    mat4 projection;
} quad_mvp;

static const char* QuadVertexShaderCode = 
    "#version 460 core\n"
    "layout (location = 0) in vec3 a_position;\n"
    
    "layout(binding = 0, std140) uniform buffer_mvp {\n"
    "    mat4 model;\n"
    "    mat4 view;\n"
    "    mat4 projection;\n"
    "};\n"
    
    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * model * vec4(a_position, 1.0);\n"
    "};\n";

static const char* QuadFragmentShaderCode = 
    "#version 460 core\n"
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

    // Buffers:
    {
        quad_vertex vertices[4] = {
            { .position = { -0.5f, -0.5f, 0.0f } },
            { .position = {  0.5f, -0.5f, 0.0f } },
            { .position = {  0.5f,  0.5f, 0.0f } },
            { .position = { -0.5f,  0.5f, 0.0f } }
        };
    
        renderer->vbo = graphics_create_buffer(vertices, sizeof(vertices), 
            BUFFER_DYNAMIC_STORAGE
        );
    }
    
    {
        unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
        renderer->ibo = graphics_create_buffer(indices, sizeof(indices), BUFFER_DYNAMIC_STORAGE);
    }

    {
        renderer->mvpHandle = graphics_create_buffer(NULL, sizeof(quad_mvp), BUFFER_DYNAMIC_STORAGE);
    }
        
    // Descriptors:
    descriptor cameraDescriptor = 
    {
        .binding = 0,
        .handle = renderer->mvpHandle,
        .type = DESCRIPTOR_TYPE_UNIFORM_BUFFER
    };
    descriptor_set mainSet = 
    {
        .descriptors = { cameraDescriptor },
        .descriptorAmount = 1
    };

    // Pipeline:
    pipeline_creation_args pipelineArgs = {
        .attributes = { attribute0 },
        .attributeAmount = 1,

        .descriptorSets = { mainSet },
        .descriptorSetAmount = 1,

        .bindingDescriptions = { bindingDescription },
        .bindingDescriptionAmount = 1,

        .topology = TOPOLOGY_TRIANGLES,
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

void quad_renderer_add_data(quad_renderer* renderer, quad_renderer_data *data)
{
    void* head = linear_allocator_alloc_aligned(&renderer->dataAllocator, sizeof(quad_renderer_data), sizeof(u64));
    memcpy(head, data, sizeof(quad_renderer_data));
    ++renderer->dataAmount;
}
void quad_renderer_clear_data(quad_renderer *renderer)
{
    renderer->dataAmount = 0;
}

void quad_renderer_set_camera(quad_renderer *renderer, camera camera)
{
    renderer->camera = camera;
}

void quad_renderer_begin_render(quad_renderer* renderer, gl_handle target)
{
    // Camera:
    camera_update_view(&renderer->camera);

    // Graphics:
    graphics_begin_render(&renderer->commandBuffer, target);
    graphics_clear();

    graphics_bind_pipeline(&renderer->commandBuffer, &renderer->pipeline);

    graphics_bind_vertex_buffer(&renderer->commandBuffer, renderer->vbo, 0, sizeof(quad_vertex));
    graphics_bind_index_buffer(&renderer->commandBuffer, renderer->ibo, INDEX_TYPE_UNSIGNED_INT);
}
void quad_renderer_render(quad_renderer* renderer)
{
    // Set camera:
    quad_mvp mvpData;
    
    glm_mat4_copy(renderer->camera.projection, mvpData.projection);
    glm_mat4_copy(renderer->camera.view, mvpData.view);

    // Render quads:
    for(u64 i = 0; i < renderer->dataAmount; ++i)
    {
        quad_renderer_data data = renderer->dataBuffer[i];
        update_transform_data(&data.transform);

        glm_mat4_copy(data.transform.data, mvpData.model);

        graphics_update_buffer(renderer->mvpHandle, &mvpData, sizeof(mvpData), 0);
        graphics_draw_indexed(&renderer->commandBuffer, 6, 1, 0, 0);
    }
}
void quad_renderer_end_render(quad_renderer* renderer)
{
    graphics_end_render(&renderer->commandBuffer);
}
