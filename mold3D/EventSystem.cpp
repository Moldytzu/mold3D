#include <mold3D/3D.h>

using namespace mold::core;

void stub();

void EventSystem::AttachCallback(EventType type, void *callback)
{
    events[type] = callback;
}

void EventSystem::DetachCallback(EventType type)
{
    events[type] = (void *)stub;
}

std::map<EventType, void *> EventSystem::GetMap()
{
    return events;
}