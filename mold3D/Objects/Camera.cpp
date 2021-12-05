#include <mold3D/3D.h>

using namespace mold::render::objects;

Camera::Camera() {}

Camera::Camera(Point3D point) : GameObject(point, {0, 0, 0}, 0, 0) {}

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
        if(!MovementIgnoreRotationX)
            coords.X += AngleX * value;
        coords.Z += AngleZ * value;
        if(!MovementIgnoreRotationY)
            coords.Y += AngleY * value;
    }
    if (direction == Direction::Right)
    {
        if(!MovementIgnoreRotationX)
            coords.Z -= -AngleX * value;  
        coords.X -= AngleZ * value;        
    }
    if (direction == Direction::Left)
    {
        if(!MovementIgnoreRotationX)
            coords.Z += -AngleX * value;  
        coords.X += AngleZ * value;    
    }
    if (direction == Direction::Backward)
    {
        if(!MovementIgnoreRotationX)
            coords.X -= AngleX * value;
        coords.Z -= AngleZ * value;
        if(!MovementIgnoreRotationY)
            coords.Y -= AngleY * value;
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