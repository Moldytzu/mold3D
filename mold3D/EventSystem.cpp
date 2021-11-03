#include <mold3D/3D.h>

using namespace mold::core;

void EventSystem::AttachCallback(int type, void* callback) {
    events.insert(std::make_pair(type,callback));
}

void EventSystem::DetachCallback(int type) {
    events.erase(events.find(type));
}

std::map<int, void*> EventSystem::GetMap() {
    return events;
}