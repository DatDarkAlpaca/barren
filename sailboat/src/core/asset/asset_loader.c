#include <assert.h>
#include <stb_image.h>
#include "asset_loader.h"
#include "asset_holder.h"

void asset_load_default_texture(asset_holder *holder, const char *filepath)
{
    asset_load_texture_spec_channels(holder, filepath, 0);
}
void asset_load_texture_spec_channels(asset_holder *holder, const char *filepath, u32 channels)
{
    for (size_t i = 0; i < holder->textureCount; ++i) 
    {
        if (strcmp(holder->textureAssets[i].filepath, filepath) == 0) 
            return &holder->textureAssets[i];
    }
    assert(holder->textureCount < holder->textureCapacity); // TODO: asset_holder_resize or proper management.

    // Channels:
    u32 usedChannels = channels ? channels : STBI_rgb_alpha;

    // Data:
    asset_texture* asset = &holder->textureAssets[holder->textureCount];
    asset->data = stbi_load(filepath, &asset->width, &asset->height, &asset->channels, usedChannels);

    // TODO: error management
    if(!asset->data)
    {
        return NULL;
    }

    asset->filepath = strdup(filepath);
    asset->channels = usedChannels;
    
    return asset;
}
