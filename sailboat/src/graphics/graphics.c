#include "graphics.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void graphics_system_initialize()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void graphics_system_late_initialize()
{
    glEnable(GL_DEPTH_TEST);
}

void graphics_present(GLFWwindow *window)
{
    glfwSwapBuffers(window);
}
