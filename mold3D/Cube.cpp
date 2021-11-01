#include <mold3D/3D.h>

using namespace mold::objects;

Cube::Cube() {}

Cube::Cube(Float3D X, Float3D Y, Float3D Z, Float3D Size) : GameObject(X, Y, Z)
{
    this->Size = Size;
}

void Cube::Draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    // Top
    glVertex3f(X + Size, Y + Size, -Z);
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X, Y + Size, -Z + Size);
    glVertex3f(X + Size, Y + Size, -Z + Size);

    // Bottom
    glVertex3f(X + Size, Y, -Z + Size);
    glVertex3f(X, Y, -Z + Size);
    glVertex3f(X, Y, -Z);
    glVertex3f(X + Size, Y, -Z);

    // Front
    glVertex3f(X + Size, Y + Size, -Z + Size);
    glVertex3f(X, Y + Size, -Z + Size);
    glVertex3f(X, Y, -Z + Size);
    glVertex3f(X + Size, Y, -Z + Size);

    // Back
    glVertex3f(X + Size, Y, -Z);
    glVertex3f(X, Y, -Z);
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X + Size, Y + Size, -Z);

    // Left
    glVertex3f(X, Y + Size, -Z + Size);
    glVertex3f(X, Y + Size, -Z);
    glVertex3f(X, Y, -Z);
    glVertex3f(X, Y, -Z + Size);

    // Right
    glVertex3f(X + Size, Y + Size, -Z);
    glVertex3f(X + Size, Y + Size, -Z + Size);
    glVertex3f(X + Size, Y, -Z + Size);
    glVertex3f(X + Size, Y, -Z);
    glEnd();
    glPopMatrix();
}