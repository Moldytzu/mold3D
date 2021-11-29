#include <mold3D/3D.h>

using namespace mold::render::objects;

Plane::Plane() {}

Plane::Plane(Point3D point, RGB color, Float3D size) : GameObject(point, color, size / 2) {}

void Plane::Draw()
{
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(color.R, color.G, color.B); // set color

    //scale up
    glScalef(Size, Size, Size);

    //move in the world
    glTranslatef(coords.X, coords.Y, coords.Z);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0 - 1.0f, 0, 0 - 1.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0 - 1.0f, 0, 1.0f + 0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0f + 0, 0, 1.0f + 0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0f + 0, 0, 0 - 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}