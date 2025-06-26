#include <glad/glad.h>
#include "pipeline.h"
#include "utils/string.h"

pipeline_creation_result graphics_create_pipeline(const pipeline_creation_args *const args)
{
    pipeline pipeline = {
        .handle = invalid_handle,
        .cullFace = args->cullFace,
        .frontFace = args->frontFace,
        .polygonMode = args->polygonMode
    };

    pipeline_creation_result result = {
        .code = GRAPHICS_PIPELINE_CREATION_FAILED,
        .pipeline = pipeline
    };

    pipeline.handle = glCreateProgram();
    glAttachShader(pipeline.handle, args->vertexShader);
    glAttachShader(pipeline.handle, args->fragmentShader);

    glLinkProgram(pipeline.handle);

    i32 success;
    char infoLog[512];
    glGetProgramiv(pipeline.handle, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(pipeline.handle, 512, NULL, infoLog);
        safer_stringcopy(result.message, 512, infoLog);
    }

    graphics_destroy_shader(args->vertexShader);
    graphics_destroy_shader(args->fragmentShader);

    return result;
}
void graphics_destroy_pipeline(pipeline* pipeline)
{
    glDeleteProgram(pipeline->handle);
    pipeline->cullFace = invalid_handle;
    pipeline->frontFace = invalid_handle;
    pipeline->polygonMode = invalid_handle;
}