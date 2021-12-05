#include <mold3D/3D.h>

using namespace mold::render::objects;

Pyramid::Pyramid(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex) : GameObject({point.X, point.Y + Size / 4, point.Z}, color, Size / 2, TextureIndex) {}

void Pyramid::Draw()
{
    BoilerPlate(
        {
            glBegin(GL_TRIANGLES);

            // Front
            glTexCoord2f(0.5, 1.0);
            glVertex3f(0, 0 + 1.0f, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0 - 1.0f, 0 - 1.0f, 0 + 1.0f);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0 + 1.0f, 0 - 1.0f, 0 + 1.0f);

            // Right
            glTexCoord2f(0.5, 1.0);
            glVertex3f(0, 0 + 1.0f, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0 + 1.0f, 0 - 1.0f, 0 + 1.0f);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0 + 1.0f, 0 - 1.0f, 0 - 1.0f);

            // Back
            glTexCoord2f(0.5, 1.0);
            glVertex3f(0, 0 + 1.0f, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0 + 1.0f, 0 - 1.0f, 0 - 1.0f);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0 - 1.0f, 0 - 1.0f, 0 - 1.0f);

            // Left
            glTexCoord2f(0.5, 1.0);
            glVertex3f(0, 0 + 1.0f, 0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(0 - 1.0f, 0 - 1.0f, 0 - 1.0f);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(0 - 1.0f, 0 - 1.0f, 0 + 1.0f);

            glEnd();

            glBegin(GL_QUADS);
            // Bottom
            glVertex3f(0 + 1.0f / 2, 0, 0 + 1.0f / 2);
            glVertex3f(0 - 1.0f / 2, 0, 0 + 1.0f / 2);
            glVertex3f(0 - 1.0f / 2, 0, 0 - 1.0f / 2);
            glVertex3f(0 + 1.0f / 2, 0, 0 - 1.0f / 2);
            glEnd();
        })
}