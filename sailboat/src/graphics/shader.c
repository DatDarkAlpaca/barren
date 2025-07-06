#include <glad/glad.h>
#include <stdlib.h>
#include "shader.h"
#include "core/errors.h"
#include "utils/string.h"

gl_handle graphics_create_shader(shader_type type, const char* const source)
{
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
            SAIL_LOG_FATAL("Invalid shader type: %d", type);
            return invalid_handle;
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
        SAIL_LOG_ERROR("Failed to compile shader: %s", infoLog);
        return invalid_handle;
    }

    return shader;
}
void graphics_destroy_shader(gl_handle shaderHandle)
{
    glDeleteShader(shaderHandle);
}