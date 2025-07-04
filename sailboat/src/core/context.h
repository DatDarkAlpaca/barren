#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/view.h"
#include "graphics/quad-renderer.h"

typedef struct context
{
    GLFWwindow* window;
    view_holder viewHolder;
    quad_renderer quadRenderer;
} context;