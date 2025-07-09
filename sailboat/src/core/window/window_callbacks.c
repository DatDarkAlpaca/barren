#include "window.h"
#include "window_callbacks.h"
#include "core/event/event_types.h"

static void on_window_close(GLFWwindow* window)
{
    windowing_internal_data* data = glfwGetWindowUserPointer(window);
    event onCloseEvent = { .type = EVT_WINDOW_CLOSE };
    data->eventCallback(data->engine, onCloseEvent);
}

void window_register_events(GLFWwindow *window)
{
    glfwSetWindowCloseCallback(window, on_window_close);
}