#include <mold3D/3D.h>

using namespace mold::render::objects;

Pyramid::Pyramid() {}

Pyramid::Pyramid(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex) : GameObject({point.X, point.Y + Size / 4, point.Z}, color, Size / 2, TextureIndex) {}

void Pyramid::Draw()
{
    glPushMatrix();

    glColor3f(color.R, color.G, color.B); // set color

    if (TextureIndex > 0)
    {
        glBindTexture(GL_TEXTURE_2D, render::GlobalTextures[TextureIndex]);
        glEnable(GL_TEXTURE_2D);
    }

    //scale up
    glScalef(Size, Size, Size);

    //move in the world
    glTranslatef(coords.X, coords.Y, coords.Z);

    glBegin(GL_TRIANGLES);

    // Front
    glVertex3f(0, 0 + 1.0f, 0);
    glVertex3f(0 - 1.0f, 0 - 1.0f, 0 + 1.0f);
    glVertex3f(0 + 1.0f, 0 - 1.0f, 0 + 1.0f);

    // Right
    glVertex3f(0, 0 + 1.0f, 0);
    glVertex3f(0 + 1.0f, 0 - 1.0f, 0 + 1.0f);
    glVertex3f(0 + 1.0f, 0 - 1.0f, 0 - 1.0f);

    // Back
    glVertex3f(0, 0 + 1.0f, 0);
    glVertex3f(0 + 1.0f, 0 - 1.0f, 0 - 1.0f);
    glVertex3f(0 - 1.0f, 0 - 1.0f, 0 - 1.0f);

    // Left
    glVertex3f(0, 0 + 1.0f, 0);
    glVertex3f(0 - 1.0f, 0 - 1.0f, 0 - 1.0f);
    glVertex3f(0 - 1.0f, 0 - 1.0f, 0 + 1.0f);

    glEnd();

    glBegin(GL_QUADS);
    // Bottom
    glVertex3f(0 + 1.0f / 2, 0, 0 + 1.0f / 2);
    glVertex3f(0 - 1.0f / 2, 0, 0 + 1.0f / 2);
    glVertex3f(0 - 1.0f / 2, 0, 0 - 1.0f / 2);
    glVertex3f(0 + 1.0f / 2, 0, 0 - 1.0f / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}