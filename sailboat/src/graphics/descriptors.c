#include <glad/glad.h>
#include "descriptors.h"

gl_handle get_descriptor_type(descriptor_type type)
{
    switch(type)
    {
        case DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            return GL_UNIFORM_BUFFER;

        case DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER:
            return GL_SHADER_STORAGE_BUFFER;

        case DESCRIPTOR_TYPE_COMBINED_TEXTURE_SAMPLER:
            return GL_TEXTURE_2D;
    }

    return invalid_handle;
}

void graphics_update_descriptor_resource(descriptor_set *set, gl_handle handle, descriptor_type type, u32 binding, u32 descriptorIndex)
{
    gl_handle glType = get_descriptor_type(type);
    if(glType == invalid_handle)
    {
        SAIL_LOG_FATAL("Invalid descriptor type: update_descriptor_resource");
        return;
    }

    set->descriptors[descriptorIndex].handle = handle;

	switch (type)
	{
		case DESCRIPTOR_TYPE_UNIFORM_BUFFER:
		case DESCRIPTOR_TYPE_SHADER_STORAGE_BUFFER:
		{
			glBindBufferBase(glType, binding, handle);
		} break;

		case DESCRIPTOR_TYPE_COMBINED_TEXTURE_SAMPLER:
		{
			glBindTextureUnit(binding, handle);
		} break;
	}
}