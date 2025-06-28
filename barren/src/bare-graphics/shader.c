#include <glad/glad.h>
#include "shader.h"
#include "utils/string.h"

shader_creation_result graphics_create_shader(shader_type type, const char* const source)
{
    shader_creation_result result = {
        .message = "",
        .code = UNKNOWN_ERROR,
        .handle = invalid_handle
    };

    u32 shaderType;
    switch (type)
    {
        case SHADER_VERTEX:
            shaderType = GL_VERTEX_SHADER;
            break;

        case SHADER_FRAGMENT:
            shaderType = GL_FRAGMENT_SHADER;
            break;

        default:
        {
            result.code = GRAPHICS_SHADER_INVALID_TYPE;
            return result;
        } break;
    }

    gl_handle shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    i32 success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        safer_stringcopy(result.message, 1024, infoLog);
        result.code = GRAPHICS_SHADER_COMPILATION_FAILED;
        return result;
    }

    result.code = SUCCESS;
    result.handle = shader;
    return result;
}
void graphics_destroy_shader(gl_handle shaderHandle)
{
    glDeleteShader(shaderHandle);
}