#include <glad/glad.h>
#include "buffer.h"
#include "handle.h"

gl_handle graphics_create_buffer(void* data, u64 size, buffer_usage_flags usageFlags)
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
