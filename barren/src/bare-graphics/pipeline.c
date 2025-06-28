#include <glad/glad.h>
#include <string.h>
#include "pipeline.h"
#include "utils/string.h"

gl_handle get_attribute_format(attribute_format format)
{
    switch (format)
    {
        case ATTRIBUTE_FORMAT_R32_SFLOAT:
            return GL_FLOAT;

        case ATTRIBUTE_FORMAT_R64_SFLOAT:
            return GL_FLOAT;

        case ATTRIBUTE_FORMAT_R32G32_SFLOAT:
            return GL_FLOAT;

        case ATTRIBUTE_FORMAT_R32G32B32_SFLOAT:
            return GL_FLOAT;

        case ATTRIBUTE_FORMAT_R32G32B32A32_SFLOAT:
            return GL_FLOAT;

        case ATTRIBUTE_FORMAT_R32G32_SINT:
            return GL_INT;

        case ATTRIBUTE_FORMAT_R32G32B32A32_UINT:
            return GL_UNSIGNED_INT;
    }

    return invalid_handle;
}
u64 get_attribute_format_size(attribute_format format)
{
    switch (format)
    {
        case ATTRIBUTE_FORMAT_R32_SFLOAT:
            return 1;

        case ATTRIBUTE_FORMAT_R64_SFLOAT:
            return 1;

        case ATTRIBUTE_FORMAT_R32G32_SFLOAT:
            return 2;

        case ATTRIBUTE_FORMAT_R32G32B32_SFLOAT:
            return 3;

        case ATTRIBUTE_FORMAT_R32G32B32A32_SFLOAT:
            return 4;

        case ATTRIBUTE_FORMAT_R32G32_SINT:
            return 2;

        case ATTRIBUTE_FORMAT_R32G32B32A32_UINT:
            return 4;
    }
    
    return invalid_handle;
}

pipeline_creation_result graphics_create_pipeline(const pipeline_creation_args *const args)
{
    pipeline pipeline = {
        .handle = invalid_handle,
        .cullFace = args->cullFace,
        .frontFace = args->frontFace,
        .polygonMode = args->polygonMode,
        .topology = args->topology,
        
        .attributeAmount = args->attributeAmount,
        .bindingDescriptionAmount = args->bindingDescriptionAmount,
    };

    memcpy(pipeline.attributes, args->attributes, args->attributeAmount * sizeof(attribute));
    memcpy(pipeline.bindingDescriptions, args->bindingDescriptions, 
        args->bindingDescriptionAmount * sizeof(binding_description));
    
    pipeline.handle = glCreateProgram();
    glAttachShader(pipeline.handle, args->vertexShader);
    glAttachShader(pipeline.handle, args->fragmentShader);

    glLinkProgram(pipeline.handle);

    i32 success;
    char infoLog[512];
    glGetProgramiv(pipeline.handle, GL_LINK_STATUS, &success);
    if (!success)
    {
        pipeline_creation_result result = {
            .code = GRAPHICS_PIPELINE_CREATION_FAILED
        };

        glGetProgramInfoLog(pipeline.handle, 512, NULL, infoLog);
        safer_stringcopy(result.message, 512, infoLog);

        return result;
    }

    graphics_destroy_shader(args->vertexShader);
    graphics_destroy_shader(args->fragmentShader);

    pipeline_creation_result result = {
        .code = SUCCESS,
        .pipeline = pipeline
    };

    return result;
}
void graphics_destroy_pipeline(pipeline* pipeline)
{
    glDeleteProgram(pipeline->handle);
    pipeline->cullFace = invalid_handle;
    pipeline->frontFace = invalid_handle;
    pipeline->polygonMode = invalid_handle;
    pipeline->topology = invalid_handle;
}