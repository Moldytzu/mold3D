#include <mold3D/3D.h>

using namespace mold::core;

void EventSystem::AttachCallback(EventType type, void* callback) {
    events.insert(std::make_pair(type,callback));
}

void EventSystem::DetachCallback(EventType type) {
    events.erase(events.find(type));
}

std::map<EventType, void*> EventSystem::GetMap() {
    return events;
}