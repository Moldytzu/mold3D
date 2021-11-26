#include <mold3D/3D.h>

void mold::core::input::LockCursor(bool locked)
{
    SDL_SetRelativeMouseMode((SDL_bool)locked);
}