#include <mold3D/3D.h>

#define NOW std::chrono::high_resolution_clock::now()
#define DIFFERENCE (double)(std::chrono::duration_cast<std::chrono::milliseconds>(NOW - engineStartedSince).count() / 1000.0f)

auto engineStartedSince = NOW;

void mold::core::logging::Info(const char *text)
{
    printf("[%.2f/Info] %s\n", DIFFERENCE, text);
    mold::gui::GlobalConsole.AddLog("[%.2f/Info] %s\n", DIFFERENCE, text);
}

void mold::core::logging::Warn(const char *text)
{
    printf("[%.2f/Warn] %s\n", DIFFERENCE, text);
    mold::gui::GlobalConsole.AddLog("[%.2f/Warn] %s\n", DIFFERENCE, text);
}

void mold::core::logging::Error(const char *text)
{
    printf("[/%.2fError] %s\n", DIFFERENCE, text);
    mold::gui::GlobalConsole.AddLog("[%.2f/Error] %s\n", DIFFERENCE, text);
}