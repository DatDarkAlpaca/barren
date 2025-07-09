#include <assert.h>
#include <string.h>
#include <stb_image.h>
#include "ephemeral.h"

void ephemeral_initialize(ephemeral* ephemeral, u64 textureCapacity)
{
    assert(ephemeral);

    ephemeral->textures = sail_memory_alloc(textureCapacity, MEMORY_TEXTURE);

    sail_linear_allocator_initialize_external(
        &ephemeral->textureAllocator,
        ephemeral->textures, textureCapacity
    );
}

asset_texture* ephemeral_get_texture_by_name(ephemeral* ephemeral, const char* filepath)
{
    assert(ephemeral);

    asset_texture* texture = NULL;
    for(u64 i = 0; i < ephemeral->textureAllocator.currentIndex; ++i)
    {
        texture = &ephemeral->textures[i];
        if(texture && strcmp(texture->filepath, filepath) != 0)
            continue;
    }

    return texture;
}

asset_texture* ephemeral_imm_load_texture(ephemeral* ephemeral, const char* filepath)
{
    assert(ephemeral);
    
    asset_texture* texture;
    if(texture = ephemeral_get_texture_by_name(ephemeral, filepath))
        return texture;

    texture = (asset_texture*)sail_linear_allocator_alloc_aligned(
        &ephemeral->textureAllocator,
        sizeof(asset_texture),
        sizeof(asset_texture)
    );

    // TODO: wrap this in another thread
    texture->data = stbi_load(filepath, &texture->width, &texture->height, &texture->channels, 0);

    if(!texture->data)
    {
        SAIL_LOG_ERROR("Failed to load texture.");
        return NULL;
    }

    texture->filepath = strdup(filepath);
    return texture;    
}
