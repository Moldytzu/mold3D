#include <mold3D/3D.h>

using namespace mold::render::objects;

Camera::Camera() {}

Camera::Camera(Point3D point) : GameObject(point, {0, 0, 0},0) {}

void Camera::Draw()
{
    glLoadIdentity();
    gluLookAt(coords.X, coords.Y, coords.Z,                   // eye -> camera position
              coords.X + AngleX, coords.Y, coords.Z + AngleZ, // center -> camera + angle
              0.0f, coords.Y, 0.0f);                          // up -> 0
}

void Camera::Move(int direction, Float3D value)
{
    if (direction == DIRECTION_FORWARD)
    {
        coords.X += AngleX * value;
        coords.Z += AngleZ * value;
        lastOP = 'w';
    }
    if (direction == DIRECTION_RIGHT)
    {
        Angle += value;
        AngleX = sin(Angle);
        AngleZ = -cos(Angle);
        lastOP = 'd';
    }
    if (direction == DIRECTION_LEFT)
    {
        Angle -= value;
        AngleX = sin(Angle);
        AngleZ = -cos(Angle);
        lastOP = 'a';
    }
    if (direction == DIRECTION_BACKWARD)
    {
        coords.X -= AngleX * value;
        coords.Z -= AngleZ * value;
        lastOP = 's';
    }
}