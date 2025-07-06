#pragma once
#include <log.h>
#include "platform.h"

void logging_subsystem_initialize();

#define SAIL_LOG_TRACE(...) { log_debug(__VA_ARGS__); platform_breakpoint(); }
