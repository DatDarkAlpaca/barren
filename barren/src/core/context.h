#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/quad-renderer.h"

typedef struct context
{
    GLFWwindow* window;
    quad_renderer quadRenderer;
} context;