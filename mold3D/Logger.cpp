#include <mold3D/3D.h>

void mold::core::logging::Info(const char* text) {
    printf("[mold3D:-:Info] %s\n", text);
}

void mold::core::logging::Warn(const char* text) {
    printf("[mold3D:-:Warn] %s\n", text);
}

void mold::core::logging::Error(const char* text) {
    printf("[mold3D:-:Error] %s\n", text);
}