#pragma once
#include "common.h"
#include "asset.h"

struct asset_holder;
asset_texture* asset_load_default_texture(struct asset_holder* holder, const char* filepath);
asset_texture* asset_load_texture_spec_channels(struct asset_holder* holder, const char* filepath, u32 channels);