#pragma once
#include "asset.h"
#include "defines.h"
#include "subsystem/sail_memory.h"

struct context;
typedef void (*on_resource_pre_load_clk)(struct context*);		     
typedef void (*on_resource_post_load_clk)(struct context*);
typedef void (*on_resource_pre_unload_clk)(struct context*);
typedef void (*on_resource_post_unload_clk)(struct context*);

typedef enum ephemerality_flags
{
    EPH_PERSISTENT               = 0,
    EPH_LOAD_ON_VIEW_LOAD        = 1 << 0,
    EPH_UNLOAD_ON_VIEW_UNLOAD    = 1 << 2,

    EPH_LOAD_ON_SCENE_LOAD       = 1 << 2,
    EPH_UNLOAD_ON_SCENE_SWAP     = 1 << 3,
    EPH_UNLOAD_ON_SCENE_UNLOAD   = 1 << 3,
} ephemerality_flags;

typedef struct ephemeral
{
    asset_texture* textures;
    sail_linear_allocator textureAllocator;
} ephemeral;

void ephemeral_initialize(ephemeral* ephemeral, u64 textureCapacity);
asset_texture* ephemeral_get_texture(ephemeral* ephemeral, asset_texture_handle handle);

asset_texture_handle ephemeral_imm_load_texture(ephemeral* ephemeral, const char* filepath);