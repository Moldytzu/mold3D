#include <mold3D/3D.h>

using namespace mold::render;

void mold::render::SetProjection(Float3D fov)
{
    int w, h;
    SDL_GetWindowSize(mold::core::GlobalWindow, &w, &h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(fov, w * 1.0 / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}
