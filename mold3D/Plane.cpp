#include <mold3D/3D.h>

using namespace mold::render::objects;

Plane::Plane() {}

Plane::Plane(Point3D point, RGB color, Float3D size) : GameObject(point, color, size / 2) {}

void Plane::Draw()
{
    glPushMatrix();

    glColor3f(color.R, color.G, color.B); // set color

    //scale up
    glScalef(Size, Size, Size);

    //move in the world
    glTranslatef(coords.X, coords.Y, coords.Z);

    glBegin(GL_QUADS);
    glVertex3f(0 - 1.0f, 0, 0 - 1.0f);
    glVertex3f(0 - 1.0f, 0, 1.0f + 0);
    glVertex3f(1.0f + 0, 0, 1.0f + 0);
    glVertex3f(1.0f + 0, 0, 0 - 1.0f);
    glEnd();

    glPopMatrix();
}