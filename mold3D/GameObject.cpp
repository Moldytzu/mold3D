#include <mold3D/3D.h>

using namespace mold::objects;

GameObject::GameObject(Point3D point, RGB color)
{
    this->coords = point;
    this->color = color;
}

GameObject::GameObject() {}

void GameObject::Draw() {}