#pragma once
#include "handle.h"
#include "common.h"

typedef enum buffer_index_type
{
	INDEX_TYPE_UNSIGNED_BYTE,
	INDEX_TYPE_UNSIGNED_SHORT,
	INDEX_TYPE_UNSIGNED_INT
} buffer_index_type;

gl_handle get_buffer_index_type(buffer_index_type type);

typedef enum buffer_usage_flags
{
    NONE                    = 0,
    BUFFER_DYNAMIC_STORAGE  = 1 << 0,
    BUFFER_MAP_READ         = 1 << 1,
    BUFFER_MAP_WRITE        = 1 << 2,
    BUFFER_PERSISTENT       = 1 << 3,
    BUFFER_COHERENT         = 1 << 4
} buffer_usage_flags;

gl_handle graphics_create_empty_buffer(buffer_usage_flags usageFlags);
gl_handle graphics_create_buffer(void* data, u64 size, buffer_usage_flags usageFlags);
void graphics_update_buffer(gl_handle bufferHandle, void* data, u64 size, u64 offset);
void graphics_destroy_buffer(gl_handle bufferHandle);