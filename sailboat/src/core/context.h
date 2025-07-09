#pragma once
#include "core/window/window.h"
#include "core/view/view_holder.h"
#include "core/ephemeral/ephemeral.h"
#include "graphics/renderer/quad-renderer.h"

typedef struct context
{
    windowing_system windowingSystem;

    ephemeral ephemeralSystem;
    view_holder viewHolder;
    quad_renderer quadRenderer;

    f32 frameDeltaTime;
} context;