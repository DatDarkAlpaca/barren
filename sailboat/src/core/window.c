#include <assert.h>
#include "window.h"

void windowing_system_initialize()
{
    if(!glfwInit())
        SAIL_LOG_FATAL("Failed to initialize the windowing system");
}

void window_create(GLFWwindow** window, u32 width, u32 height, const char* title)
{
    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!*window)
        SAIL_LOG_FATAL("Failed to create window");

    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        SAIL_LOG_FATAL("Failed to initialize glad");
}

void window_set_title(GLFWwindow *window, const char *title)
{
    assert(window);
    glfwSetWindowTitle(window, title);
}
