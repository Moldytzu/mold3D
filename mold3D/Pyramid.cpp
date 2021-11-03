#include <mold3D/3D.h>

using namespace mold::render::objects;

Pyramid::Pyramid() {}

Pyramid::Pyramid(Point3D point, RGB color, Float3D Size) : GameObject({point.X,point.Y+Size/2,point.Z}, color, Size/2) {}

void Pyramid::Draw()
{
    glColor3f(color.R, color.G, color.B); // set color

    glBegin(GL_TRIANGLES);

    // Front
    glVertex3f(coords.X, coords.Y + Size, coords.Z);
    glVertex3f(coords.X - Size, coords.Y - Size, coords.Z + Size);
    glVertex3f(coords.X + Size, coords.Y - Size, coords.Z + Size);

    // Right
    glVertex3f(coords.X, coords.Y + Size, coords.Z);
    glVertex3f(coords.X + Size, coords.Y - Size, coords.Z + Size);
    glVertex3f(coords.X + Size, coords.Y - Size, coords.Z - Size);

    // Back
    glVertex3f(coords.X, coords.Y + Size, coords.Z);
    glVertex3f(coords.X + Size, coords.Y - Size, coords.Z - Size);
    glVertex3f(coords.X - Size, coords.Y - Size, coords.Z - Size);

    // Left
    glVertex3f(coords.X, coords.Y + Size, coords.Z);
    glVertex3f(coords.X - Size, coords.Y - Size, coords.Z - Size);
    glVertex3f(coords.X - Size, coords.Y - Size, coords.Z + Size);

    glEnd();

    glBegin(GL_QUADS);
    // Bottom
    glVertex3f(coords.X + Size / 2, coords.Y, coords.Z + Size / 2);
    glVertex3f(coords.X - Size / 2, coords.Y, coords.Z + Size / 2);
    glVertex3f(coords.X - Size / 2, coords.Y, coords.Z - Size / 2);
    glVertex3f(coords.X + Size / 2, coords.Y, coords.Z - Size / 2);
    glEnd();
}