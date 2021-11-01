#include <mold3D/3D.h>

using namespace mold::objects;

Cube::Cube() {}

Cube::Cube(Point3D point, RGB color, Float3D Size) : GameObject(point, color)
{
    this->Size = Size;
}

void Cube::Draw()
{
    glPushMatrix();

    glColor3f(color.R, color.G, color.B); // set color

    glBegin(GL_QUADS);
    // Top
    glVertex3f(coords.X + Size, coords.Y + Size, -coords.Z);
    glVertex3f(coords.X, coords.Y + Size, -coords.Z);
    glVertex3f(coords.X, coords.Y + Size, -coords.Z + Size);
    glVertex3f(coords.X + Size, coords.Y + Size, -coords.Z + Size);

    // Bottom
    glVertex3f(coords.X + Size, coords.Y, -coords.Z + Size);
    glVertex3f(coords.X, coords.Y, -coords.Z + Size);
    glVertex3f(coords.X, coords.Y, -coords.Z);
    glVertex3f(coords.X + Size, coords.Y, -coords.Z);

    // Front
    glVertex3f(coords.X + Size, coords.Y + Size, -coords.Z + Size);
    glVertex3f(coords.X, coords.Y + Size, -coords.Z + Size);
    glVertex3f(coords.X, coords.Y, -coords.Z + Size);
    glVertex3f(coords.X + Size, coords.Y, -coords.Z + Size);

    // Back
    glVertex3f(coords.X + Size, coords.Y, -coords.Z);
    glVertex3f(coords.X, coords.Y, -coords.Z);
    glVertex3f(coords.X, coords.Y + Size, -coords.Z);
    glVertex3f(coords.X + Size, coords.Y + Size, -coords.Z);

    // Left
    glVertex3f(coords.X, coords.Y + Size, -coords.Z + Size);
    glVertex3f(coords.X, coords.Y + Size, -coords.Z);
    glVertex3f(coords.X, coords.Y, -coords.Z);
    glVertex3f(coords.X, coords.Y, -coords.Z + Size);

    // Right
    glVertex3f(coords.X + Size, coords.Y + Size, -coords.Z);
    glVertex3f(coords.X + Size, coords.Y + Size, -coords.Z + Size);
    glVertex3f(coords.X + Size, coords.Y, -coords.Z + Size);
    glVertex3f(coords.X + Size, coords.Y, -coords.Z);
    glEnd();
    glPopMatrix();
}