#pragma once
#include "common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

u64 windowing_system_initialize();

u64 window_create(GLFWwindow** window, u32 width, u32 height, const char* title);

void window_set_title(GLFWwindow* window, const char* title);