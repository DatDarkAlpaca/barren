#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/common.h"
#include "core/event/event.h"

typedef struct windowing_internal_data
{
    event_callback eventCallback;
    struct engine* engine;
} windowing_internal_data;

typedef struct windowing_system
{
    GLFWwindow* window;
    windowing_internal_data data;
} windowing_system; 

void windowing_system_initialize(windowing_system* windowingSystem, struct engine* engine, event_callback eventCallback);

void window_create(windowing_system* windowingSystem, u32 width, u32 height, const char* title);

void window_set_title(windowing_system* windowingSystem, const char* title);