#pragma once
#include "common.h"

typedef struct asset_texture
{
    const char* filepath;
    byte* data;
    u32 width;
    u32 height;
    u32 depth;
    u32 channels;
} asset_texture;

typedef u64 asset_texture_handle;