#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/view.h"
#include "core/asset/asset_holder.h"
#include "graphics/renderer/quad-renderer.h"

typedef struct context
{
    GLFWwindow* window;

    asset_holder assetHolder;
    view_holder viewHolder;
    quad_renderer quadRenderer;
} context;