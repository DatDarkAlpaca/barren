#include <assert.h>
#include "window.h"
#include "window_callbacks.h"

void windowing_system_initialize(windowing_system* windowingSystem, struct engine* engine, event_callback eventCallback)
{
    assert(windowingSystem);
    assert(engine);

    if(!glfwInit())
        SAIL_LOG_FATAL("Failed to initialize the windowing system");
    
    windowingSystem->data.eventCallback = eventCallback;
    windowingSystem->data.engine = engine;
}

void window_create(windowing_system* windowingSystem, u32 width, u32 height, const char *title)
{
    assert(windowingSystem);

    windowingSystem->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!windowingSystem->window)
        SAIL_LOG_FATAL("Failed to create window");

    glfwSetWindowUserPointer(windowingSystem->window, &windowingSystem->data);
    glfwMakeContextCurrent(windowingSystem->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        SAIL_LOG_FATAL("Failed to initialize glad");

        
    window_register_events(windowingSystem->window);
}

void window_set_title(windowing_system* windowingSystem, const char *title)
{
    assert(windowingSystem);
    glfwSetWindowTitle(windowingSystem->window, title);
}
