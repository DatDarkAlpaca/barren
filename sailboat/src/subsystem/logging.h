#pragma once
#include <log.h>
#include "platform.h"

void logging_subsystem_initialize();

#if defined(DEBUG) || defined(_DEBUG)
    #define SAIL_LOG_TRACE(...)    log_trace(__VA_ARGS__)
    #define SAIL_LOG_DEBUG(...)    log_debug(__VA_ARGS__)
    #define SAIL_LOG_INFO(...)     log_info(__VA_ARGS__)
    #define SAIL_LOG_WARN(...)     log_warn(__VA_ARGS__)
    #define SAIL_LOG_ERROR(...)    log_error(__VA_ARGS__)
    #define SAIL_LOG_FATAL(...)    { log_fatal(__VA_ARGS__); platform_breakpoint(); }
#else
    #define SAIL_LOG_TRACE(...)
    #define SAIL_LOG_DEBUG(...)
    #define SAIL_LOG_INFO(...)
    #define SAIL_LOG_WARN(...)
    #define SAIL_LOG_ERROR(...)
    #define SAIL_LOG_FATAL(...)    { log_fatal(__VA_ARGS__); platform_breakpoint(); }   // todo: error popup
#endif