#include <mold3D/3D.h>

using namespace mold::render::objects;

Plane::Plane(Point3D point, RGB color, Float3D size, uint32_t TextureIndex) : GameObject(point, color, size / 2, TextureIndex) {}

void Plane::Draw()
{
    BoilerPlate(
        {
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(0 - 1.0f, 0, 0 - 1.0f);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0 - 1.0f, 0, 1.0f + 0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(1.0f + 0, 0, 1.0f + 0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(1.0f + 0, 0, 0 - 1.0f);
            glEnd();
        })
}