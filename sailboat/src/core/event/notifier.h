#pragma once
#include "event.h"

typedef struct notifier
{
    event* event;
} notifier;

typedef bool (*notification_callback)(event, void*);
void notifier_notify(notifier* notifier, u64 eventType, notification_callback callback, void* args);