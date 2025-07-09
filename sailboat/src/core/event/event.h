#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "defines.h"

typedef struct event
{
    u64 type;
    bool handled;
    void* data;
} event;

struct engine;
typedef void (*event_callback)(struct engine*, event);