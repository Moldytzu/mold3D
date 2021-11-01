#include <mold3D/3D.h>

using namespace mold::objects;

Camera::Camera() {}

Camera::Camera(Point3D point) : GameObject(point, {0, 0, 0}) {}

void Camera::Draw()
{
    glLoadIdentity();
    gluLookAt(coords.X, coords.Y, coords.Z,                   // eye -> camera position
              coords.X + AngleX, coords.Y, coords.Z + AngleZ, // center -> camera + angle
              0.0f, coords.Y, 0.0f);                          // up -> 0
}

void Camera::Update(bool *keys)
{
    if (keys['W'] || keys['w'])
    {
        coords.X += AngleX * 0.05f;
        coords.Z += AngleZ * 0.05f;
    }
    if (keys['D'] || keys['d'])
    {
        Angle += 0.05f;
        AngleX = sin(Angle);
        AngleZ = -cos(Angle);
    }
    if (keys['a'] || keys['a'])
    {
        Angle -= 0.05f;
        AngleX = sin(Angle);
        AngleZ = -cos(Angle);
    }
    if (keys['s'] || keys['s'])
    {
        coords.X -= AngleX * 0.05f;
        coords.Z -= AngleZ * 0.05f;
    }
}