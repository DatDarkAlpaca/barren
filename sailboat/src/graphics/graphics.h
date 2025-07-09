#pragma once
#include <glad/glad.h>

#include "handle.h"
#include "common.h"
#include "core/window/window.h"

void graphics_system_initialize();
void graphics_system_late_initialize();

void graphics_present(struct windowing_system* window);

