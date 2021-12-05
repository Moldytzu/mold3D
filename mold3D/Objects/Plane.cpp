#include <mold3D/3D.h>

using namespace mold::render::objects;

Plane::Plane() {}

Plane::Plane(Point3D point, RGB color, Float3D size, uint32_t TextureIndex) : GameObject(point, color, size / 2, TextureIndex) {}

void Plane::Draw()
{
    glPushMatrix();

    if (TextureIndex > 0)
    {
        glBindTexture(GL_TEXTURE_2D, render::GlobalTextures[TextureIndex]);
        glEnable(GL_TEXTURE_2D);
    }

    glColor3f(color.R, color.G, color.B); // set color

    //move in the world
    glTranslatef(coords.X, coords.Y, coords.Z);

    //scale up
    glScalef(Size, Size, Size);

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

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}