#pragma once
#include <glad/glad.h>
#include "window.h"
#include "handle.h"
#include "common.h"

void graphics_system_initialize();
void graphics_system_late_initialize();

void graphics_present(GLFWwindow* window);

