#include <glad/glad.h>
#include "buffer.h"
#include "handle.h"

gl_handle get_buffer_index_type(buffer_index_type type)
{
    switch (type)
    {
        case INDEX_TYPE_UNSIGNED_BYTE:
            return GL_UNSIGNED_BYTE;

        case INDEX_TYPE_UNSIGNED_SHORT:
            return GL_UNSIGNED_SHORT;

        case INDEX_TYPE_UNSIGNED_INT:
            return GL_UNSIGNED_INT;
    }

    return invalid_handle;
}

gl_handle graphics_create_empty_buffer(buffer_usage_flags usageFlags)
{
    gl_handle bufferHandle;
    glCreateBuffers(1, &bufferHandle);

    glNamedBufferStorage(bufferHandle, 0, NULL, usageFlags);
    return bufferHandle;
}
gl_handle graphics_create_buffer(void *data, u64 size, buffer_usage_flags usageFlags)
{
    gl_handle bufferHandle;
    glCreateBuffers(1, &bufferHandle);

    u32 flags = 0;
    if (usageFlags & BUFFER_DYNAMIC_STORAGE)
        flags |= GL_DYNAMIC_STORAGE_BIT;

    else if (usageFlags & BUFFER_MAP_READ)
        flags |= GL_MAP_READ_BIT;

    else if (usageFlags & BUFFER_MAP_WRITE)
        flags |= GL_MAP_WRITE_BIT;

    else if (usageFlags & BUFFER_PERSISTENT)
        flags |= GL_MAP_PERSISTENT_BIT;

    else if (usageFlags & BUFFER_COHERENT)
        flags |= GL_MAP_COHERENT_BIT;

    glNamedBufferStorage(bufferHandle, size, data, flags);
    return bufferHandle;
}
void graphics_update_buffer(gl_handle bufferHandle, void *data, u64 size, u64 offset)
{
    glNamedBufferSubData(bufferHandle, offset, size, data);
}
void graphics_destroy_buffer(gl_handle bufferHandle)
{
    glDeleteBuffers(1, &bufferHandle);
}
