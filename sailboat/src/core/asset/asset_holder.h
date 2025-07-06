#pragma once
#include <stdlib.h>
#include <assert.h>
#include "asset.h"

typedef struct asset_holder
{
    asset_texture* textureAssets;
    u64 textureCount;
    u64 textureCapacity;
} asset_holder;

typedef struct asset_holder_params
{
    u64 textureCapacity;
} asset_holder_params;

void asset_holder_initialize(asset_holder* holder, const asset_holder_params* const params);