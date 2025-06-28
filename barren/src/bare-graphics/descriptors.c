#include <glad/glad.h>
#include "descriptors.h"

gl_handle get_buffer_descriptor_type(descriptor_type type)
{
    switch(type)
    {
        case DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            return GL_UNIFORM_BUFFER;

        case DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER:
            return GL_SHADER_STORAGE_BUFFER;
    }

    return invalid_handle;
}