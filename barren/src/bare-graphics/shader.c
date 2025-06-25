#include "shader.h"
#include <glad/glad.h>

shader_creation_result graphics_create_shader(shader_type type, const char* const source)
{
    shader_creation_result result = {
        .message = "",
        .code = UNKNOWN_ERROR,
        .handle = invalid_handle
    };

    u32 shaderType;
    switch(type)
    {
        case SHADER_VERTEX:
            shaderType = GL_VERTEX_SHADER;

        case SHADER_FRAGMENT:
            shaderType = GL_FRAGMENT_SHADER;
    }

    gl_handle shader = glCreateShader(shaderType);
    glCompileShader(shader);
    
    i32 success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        strcpy_s(result.message, 512, infoLog);
        result.code = GRAPHICS_SHADER_COMPILATION_FAILED;
        return result;
    }

    result.handle = shader;
    return result;
}
void graphics_destroy_shader(gl_handle shaderHandle)
{
    glDeleteShader(shaderHandle);
}