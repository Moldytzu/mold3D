#include <mold3D/3D.h>

using namespace mold::render::objects;

Camera::Camera() {}

Camera::Camera(Point3D point) : GameObject(point, {0, 0, 0}, 0) {}

void Camera::Draw()
{
    glLoadIdentity();
    gluLookAt(coords.X, coords.Y, coords.Z,                            // eye -> camera position
              coords.X + AngleX, coords.Y + AngleY, coords.Z + AngleZ, // center -> camera + angle
              0.0f, coords.Y, 0.0f);                                   // up -> 0
}

void Camera::Move(Direction direction, Float3D value)
{
    if (direction == Direction::Forward)
    {
        coords.X += AngleX * value;
        coords.Z += AngleZ * value;
    }
    if (direction == Direction::Right)
    {
        coords.X += value;
    }
    if (direction == Direction::Left)
    {
        coords.X -= value;
    }
    if (direction == Direction::Backward)
    {
        coords.X -= AngleX * value;
        coords.Z -= AngleZ * value;
    }
}

void Camera::Rotate(Direction direction, Float3D value)
{
    if (direction == Direction::Forward)
    {
        AngleY += (float)value;
    }
    if (direction == Direction::Right)
    {
        Angle += value;
        AngleX = sin(Angle);
        AngleZ = -cos(Angle);
    }
    if (direction == Direction::Left)
    {
        Angle -= value;
        AngleX = sin(Angle);
        AngleZ = -cos(Angle);
    }
    if (direction == Direction::Backward)
    {
        AngleY -= (float)value;
    }
}