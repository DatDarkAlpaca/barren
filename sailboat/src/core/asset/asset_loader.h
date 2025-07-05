#pragma once
#include "common.h"

struct asset_holder;
void asset_load_default_texture(struct asset_holder* holder, const char* filepath);
void asset_load_texture_spec_channels(struct asset_holder* holder, const char* filepath, u32 channels);