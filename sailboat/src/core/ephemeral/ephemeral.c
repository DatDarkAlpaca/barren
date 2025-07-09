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

asset_texture* ephemeral_get_texture(ephemeral* ephemeral, asset_texture_handle handle)
{
    assert(ephemeral);
    assert(handle >= 0);
    assert(handle < ephemeral->textureAllocator.currentIndex);

    asset_texture* texture = &ephemeral->textures[handle]; 
    if(!texture)
    {
        SAIL_LOG_FATAL("Attempted to fetch texture at invalid handle: %d", handle);
        return NULL;
    }

    return texture;
}

asset_texture_handle ephemeral_imm_load_texture(ephemeral* ephemeral, const char* filepath)
{
    assert(ephemeral);
    
    asset_texture* texture = NULL;
    for(asset_texture_handle i = 0; i < ephemeral->textureAllocator.currentIndex; ++i)
    {
        if(strcmp(filepath, ephemeral->textures[i].filepath) == 0)
            return i;
    }

    u64 textureHandle = ephemeral->textureAllocator.currentIndex;
    texture = (asset_texture*)sail_linear_allocator_alloc_aligned(
        &ephemeral->textureAllocator,
        sizeof(asset_texture),
        sizeof(asset_texture)
    );

    // TODO: wrap this in another thread
    texture->filepath = strdup(filepath);
    texture->data = stbi_load(filepath, &texture->width, &texture->height, &texture->channels, 0);

    if(!texture->data)
    {
        SAIL_LOG_ERROR("Failed to load texture.");
        return invalid_handle;
    }

    return textureHandle;
}
