#pragma one
#include "defines.h"

extern void platform_initialize();
extern void platform_shutdown();

extern void platform_breakpoint();

extern void* platform_alloc(u64 size);
extern void platform_free(void* block);
extern void platform_zero_mem(void* block, u64 size);

typedef void* (*thread_routine)(void*);
extern void* platform_create_thread(thread_routine routine, void* argument);