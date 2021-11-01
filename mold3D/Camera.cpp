#include <mold3D/3D.h>

using namespace mold::objects;

Camera::Camera() {}

Camera::Camera(Float3D X, Float3D Y, Float3D Z) : GameObject(X, Y, Z) {}

void Camera::Draw()
{
    glLoadIdentity();
    gluLookAt(X, Y, Z,                   // eye -> camera position
              X + AngleX, Y, Z + AngleZ, // center -> camera + angle
              0.0f, Y, 0.0f);            // up -> 0
}

void Camera::Update(bool *keys)
{
    if (keys['W'] || keys['w'])
    {
        X += AngleX * 0.05f;
        Z += AngleZ * 0.05f;
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
        X -= AngleX * 0.05f;
        Z -= AngleZ * 0.05f;
    }
}