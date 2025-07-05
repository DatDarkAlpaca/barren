#include <assert.h>
#include "window.h"

u64 windowing_system_initialize()
{
    if(!glfwInit())
        return GLFW_FAILED_INIT;

    return SUCCESS;
}

u64 window_create(GLFWwindow** window, u32 width, u32 height, const char* title)
{
    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!*window)
        return GLFW_FAILED_WINDOW;

    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return GLAD_FAILED_INIT;

    return SUCCESS;
}

void window_set_title(GLFWwindow *window, const char *title)
{
    assert(window);
    glfwSetWindowTitle(window, title);
}
