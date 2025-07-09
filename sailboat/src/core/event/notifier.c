#include "notifier.h"

void notifier_notify(notifier *notifier, u64 eventType, notification_callback callback, void *args)
{
    if(notifier->event->type != eventType)
        return;

    notifier->event->handled |= callback(args);
}
