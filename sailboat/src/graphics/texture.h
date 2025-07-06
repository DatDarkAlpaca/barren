#pragma once
#include "handle.h"

typedef enum texture_type
{
    TEXTURE_UNDEFINED = 0,
    TEXTURE_2D,
    TEXTURE_2D_ARRAY,
    TEXTURE_3D
} texture_type;

typedef enum wrap_mode
{
    WRAP_MODE_UNDEFINED = 0,
    WRAP_MODE_REPEAT = 0,
    WRAP_MODE_MIRRORED_REPEAT,
    WRAP_MODE_CLAMP_TO_EDGE,
    WRAP_MODE_CLAMP_TO_BORDER
} wrap_mode;

typedef enum filter_mode
{
    FILTER_MODE_UNDEFINED = 0,
    FILTER_MODE_NEAREST,
    FILTER_MODE_LINEAR,
    FILTER_MODE_BILINEAR,
    FILTER_MODE_TRILINEAR
} filter_mode;

typedef enum texture_format
{
    TEXTURE_FORMAT_UNDEFINED = 0,
    TEXTURE_FORMAT_R8_UNORM,
    TEXTURE_FORMAT_RG8_UNORM,
    TEXTURE_FORMAT_RGB8_UNORM,
    TEXTURE_FORMAT_RGBA8_UNORM,
    TEXTURE_FORMAT_RGBA16_SFLOAT,

    TEXTURE_FORMAT_DEPTH_16_UNORM,
    TEXTURE_FORMAT_DEPTH_STENCIL16_S8U_INT,
    
    TEXTURE_FORMAT_BGRA8_UNORM
} texture_format;

typedef struct texture_args
{
    texture_type type;
    texture_format format;
    u32 width;
    u32 height;
    u32 depth;

    wrap_mode wrapS;
    wrap_mode wrapT;
    wrap_mode wrapR;

    filter_mode minFilter;
    filter_mode magFilter;

    bool generateMipmaps;
} texture_args;

gl_handle graphics_create_texture(const texture_args* const args);