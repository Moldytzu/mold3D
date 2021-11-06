#include <mold3D/3D.h>

using namespace mold;

size_t usedMemory;

void *operator new(size_t size)
{
    profiler::TrackAllocMemory(size);
    return malloc(size);
}

void operator delete(void *ptr, size_t size)
{
    profiler::TrackFreeMemory(size);
    free(ptr);
}

void profiler::TrackAllocMemory(size_t bytes)
{
    usedMemory += bytes;
}

void profiler::TrackFreeMemory(size_t bytes)
{
    usedMemory -= bytes;
}

size_t profiler::GetTrackedMemory()
{
    return usedMemory;
}