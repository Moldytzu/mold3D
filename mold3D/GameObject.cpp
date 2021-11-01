#include <mold3D/3D.h>

using namespace mold::objects;

GameObject::GameObject(Point3D point, RGB color, Float3D Size)
{
    this->coords = point;
    this->color = color;
    this->Size = Size;
}

GameObject::GameObject() {}

void GameObject::Draw() {}