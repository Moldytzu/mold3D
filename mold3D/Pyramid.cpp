#include <mold3D/3D.h>

using namespace mold::objects;

Pyramid::Pyramid() {}

Pyramid::Pyramid(Float3D X, Float3D Y, Float3D Z, Float3D Size) : GameObject(X, Y, Z)
{
    this->Size = Size;
}

void Pyramid::Draw()
{
    glPushMatrix();
    glBegin(GL_TRIANGLES);

    // Front
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X - Size, Y - Size, -Z + Size);
    glVertex3f(X + Size, Y - Size, -Z + Size);

    // Right
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X + Size, Y - Size, -Z + Size);
    glVertex3f(X + Size, Y - Size, -Z - Size);

    // Back
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X + Size, Y - Size, -Z - Size);
    glVertex3f(X - Size, Y - Size, -Z - Size);

    // Left
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X - Size, Y - Size, -Z - Size);
    glVertex3f(X - Size, Y - Size, -Z + Size);

    glEnd();

    glBegin(GL_QUADS);
    // Bottom
    glVertex3f(X + Size / 2, Y, Z + Size / 2);
    glVertex3f(X - Size / 2, Y, Z + Size / 2);
    glVertex3f(X - Size / 2, Y, Z - Size / 2);
    glVertex3f(X + Size / 2, Y, Z - Size / 2);
    glEnd();
    glPopMatrix();
}