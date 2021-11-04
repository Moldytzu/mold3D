#include <mold3D/3D.h>

using namespace mold::render;

void mold::render::SetProjection(Float3D fov) {
    SDL_Window* win = mold::core::GetWindow();
    int w,h;
    SDL_GetWindowSize(win,&w,&h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(fov, w * 1.0 / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}