#include "window.h"
#include "window_callbacks.h"
#include "core/event/event_types.h"

static void on_window_close(GLFWwindow* window)
{
    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event e = { .type = EVT_WINDOW_CLOSE };
    data->eventCallback(data->engine, e);
}
static void on_window_maximize(GLFWwindow* window)
{
    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event e = { .type = EVT_WINDOW_MAXIMIZED };
    data->eventCallback(data->engine, e);
}
static void on_window_focus_changed(GLFWwindow* window)
{
    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event e = { .type = EVT_WINDOW_FOCUS_CHANGED };
    data->eventCallback(data->engine, e);
}

static void on_window_size_resize(GLFWwindow* window, int width, int height)
{
    i32 sizes[2] = { width, height };

    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event e = { .type = EVT_WINDOW_RESIZE, .data = sizes };
    data->eventCallback(data->engine, e);
}
static void on_window_framebuffer_resize(GLFWwindow* window, int width, int height)
{
    i32 sizes[2] = { width, height };

    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event e = { .type = EVT_WINDOW_FRAMEBUFFER_RESIZE, .data = sizes };
    data->eventCallback(data->engine, e);
}
static void on_window_content_scale_resize(GLFWwindow* window, int xScale, int yScale)
{
    i32 sizes[2] = { xScale, yScale };

    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event e = { .type = EVT_WINDOW_CONTENT_SCALE, .data = sizes };
    data->eventCallback(data->engine, e);
}

void window_register_events(GLFWwindow *window)
{
    glfwSetWindowCloseCallback(window, on_window_close);
    glfwSetWindowMaximizeCallback(window, on_window_maximize);
    glfwSetWindowFocusCallback(window, on_window_focus_changed);

    glfwSetWindowSizeCallback(window, on_window_size_resize);
    glfwSetFramebufferSizeCallback(window, on_window_framebuffer_resize);
}