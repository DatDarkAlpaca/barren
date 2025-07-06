#include "asset_holder.h"

void asset_holder_initialize(asset_holder *holder, const asset_holder_params *const params)
{
    assert(holder);

    holder->textureAssets = (asset_texture*)calloc(params->textureCapacity, sizeof(asset_texture));
    holder->textureCapacity = params->textureCapacity;
    holder->textureCount = 0;
}