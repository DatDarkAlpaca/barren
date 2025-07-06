#include <glad/glad.h>
#include <stdbool.h>
#include "texture.h"

static gl_handle get_wrap_mode(wrap_mode mode)
{
	switch (mode)
	{
		case WRAP_MODE_REPEAT:
			return GL_REPEAT;

		case WRAP_MODE_MIRRORED_REPEAT:
			return GL_MIRRORED_REPEAT;

		case WRAP_MODE_CLAMP_TO_EDGE:
			return GL_CLAMP_TO_EDGE;

		case WRAP_MODE_CLAMP_TO_BORDER:
			return GL_CLAMP_TO_BORDER;
	}

    SAIL_LOG_ERROR("Invalid/unspecified texture wrap mode: %d. Default: GL_REPEAT", mode);
	return GL_REPEAT;
}

static gl_handle get_filter_mode(filter_mode mode, bool isMinFilter)
{
	if (isMinFilter)
	{
		switch (mode)
		{
			case FILTER_MODE_NEAREST:
				return GL_NEAREST;

			case FILTER_MODE_LINEAR:
				return GL_LINEAR;

			case FILTER_MODE_BILINEAR:
				return GL_LINEAR_MIPMAP_NEAREST;

			case FILTER_MODE_TRILINEAR:
				return GL_LINEAR_MIPMAP_LINEAR;
		}
	}
	else
	{
		switch (mode)
		{
			case FILTER_MODE_NEAREST:
				return GL_NEAREST;

			case FILTER_MODE_LINEAR:
				return GL_LINEAR;

			case FILTER_MODE_BILINEAR:
				return GL_LINEAR;

			case FILTER_MODE_TRILINEAR:
				return GL_LINEAR;
		}
	}
	SAIL_LOG_ERROR("Invalid/ unspecified texture filter mode: %d. Default: GL_NEAREST", mode);
	return GL_REPEAT;
}

static gl_handle get_texture_format(texture_format format)
{
	switch (format)
	{
		case TEXTURE_FORMAT_DEPTH_16_UNORM:
			return GL_DEPTH_COMPONENT;

		case TEXTURE_FORMAT_DEPTH_STENCIL16_S8U_INT:
			return GL_DEPTH_STENCIL;

		case TEXTURE_FORMAT_R8_UNORM:
			return GL_R8;

		case TEXTURE_FORMAT_RG8_UNORM:
			return GL_RG8;

		case TEXTURE_FORMAT_RGB8_UNORM:
			return GL_RGB8;

		case TEXTURE_FORMAT_RGBA8_UNORM:
			return GL_RGBA8;

		case TEXTURE_FORMAT_BGRA8_UNORM:
			return GL_BGRA;
	}
	SAIL_LOG_ERROR("Invalid/unspecified texture format: %d. Default: GL_RGBA", format);
	return GL_RGBA;
}

gl_handle graphics_create_texture(const texture_args* const args)
{
    u64 target;
    switch(args->type)
    {
        case TEXTURE_2D: 
            target = GL_TEXTURE_2D;
            break;

        case TEXTURE_2D_ARRAY: 
            target = GL_TEXTURE_2D_ARRAY;
            break;

        case TEXTURE_3D: 
            target = GL_TEXTURE_3D;
            break;

        default:
        {
            SAIL_LOG_FATAL("Invalid texture type: %d", args->type);
            return invalid_handle;
        } break;
    }

    gl_handle texture;
    glCreateTextures(target, 1, &texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, get_wrap_mode(args->wrapS));
	glTextureParameteri(texture, GL_TEXTURE_WRAP_T, get_wrap_mode(args->wrapT));
	if (args->type == TEXTURE_3D)
		glTextureParameteri(texture, GL_TEXTURE_WRAP_R, get_wrap_mode(args->wrapR));

	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, get_filter_mode(args->minFilter, args->generateMipmaps));
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, get_filter_mode(args->magFilter, false));

	if (args->generateMipmaps)
		glGenerateTextureMipmap(texture);

    gl_handle textureFormat = get_texture_format(args->format);
    switch (args->type)
	{
		case TEXTURE_2D:
			glTextureStorage2D(
				texture,
				1,
				textureFormat,
				args->width,
				args->height
			);
			break;
        
		case TEXTURE_2D_ARRAY:
		case TEXTURE_3D:
			glTextureStorage3D(
				texture,
				1,
				textureFormat,
				args->width,
				args->height,
				args->depth
			);
			break;
	}

    return texture;
}