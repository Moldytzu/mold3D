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

void mold::gui::Profiler::Draw()
{
    if (!Enabled)
        return;
    const float DISTANCE = 7.5f;
    ImGui::SetNextWindowPos(ImVec2(DISTANCE, DISTANCE), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.5f);
    if (ImGui::Begin("Profiler Window", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
    {
        ImGui::Text("mold3D Profiler\n");
        ImGui::Separator();
        //need to optimize this
        size_t val = usedMemory / 1024 / 1024;
        if (val == 0)
            ImGui::Text("Allocated %lu KB on the heap\n", usedMemory / 1024);
        else
            ImGui::Text("Allocated %lu MB on the heap\n", val);
        ImGui::Separator();
        ImGui::Text("FPS: %u\n", mold::core::time::FPS);
        ImGui::Text("Frame drawing took: %u ms\n", (int)(mold::core::time::DeltaTime * 1000));
        ImGui::Separator();
        ImGui::Text("Press INSERT to close overlay\n");
    }
    ImGui::End();
}