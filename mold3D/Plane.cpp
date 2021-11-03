#include <mold3D/3D.h>

using namespace mold::render::objects;

Plane::Plane() {}

Plane::Plane(Point3D point, RGB color, Float3D Size) : GameObject(point, color, Size / 2) {}

void Plane::Draw()
{
    glColor3f(color.R, color.G, color.B); // set color

    glBegin(GL_QUADS);
    glVertex3f(coords.X - Size, coords.Y, coords.Z - Size);
    glVertex3f(coords.X - Size, coords.Y, Size + coords.Z);
    glVertex3f(Size + coords.X, coords.Y, Size + coords.Z);
    glVertex3f(Size + coords.X, coords.Y, coords.Z - Size);
    glEnd();
}