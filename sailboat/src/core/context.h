#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/view/view_holder.h"
#include "core/ephemeral/ephemeral.h"
#include "graphics/renderer/quad-renderer.h"

typedef struct context
{
    GLFWwindow* window;

    ephemeral ephemeralSystem;
    view_holder viewHolder;
    quad_renderer quadRenderer;

    f32 frameDeltaTime;
} context;